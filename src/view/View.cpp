//
// Created by nico on 11/9/24.
//
#include "View.hpp"

#include <algorithm>
#include <charconv>
#include <iostream>

#include "Constants.hpp"

View::View(const SDLManager& sdl_manager): renderer(sdl_manager.getRenderer()),
                                           grass_texture(sdl_manager.getGrassTexture()),
                                           wall_texture(sdl_manager.getWallTexture()),
                                           font(sdl_manager.getFont()) {
}

void View::render(const Model& model) const {
    SDL_RenderClear(renderer);
    renderTileMap(model.getGrid());
    renderPlayer(model.getPlayer());
    renderProjectiles(model.getPlayer().getWeapon());
    for (const Zombie& zombie: model.getZombies()) {
        renderLivingCircle(zombie);
    }
    renderScore(model.getHighScore(), "High score: ", 50);
    renderScore(model.getPlayer().getScore(), "Current score: ", 100);
    SDL_RenderPresent(renderer);
}

void View::renderTileMap(const Grid& grid) const {
    const std::vector<std::vector<Tile> >& tile_map = grid.getTileMap();
    for (const auto& i: tile_map) {
        for (const auto& tile: i) {
            SDL_Rect render_rect = {
                static_cast<int>(tile.getLeft()), static_cast<int>(tile.getTop()), Constants::TILE_SIZE,
                Constants::TILE_SIZE
            };
            if (tile.getTileType() == TileType::Walkable) {
                SDL_RenderCopy(renderer, grass_texture, nullptr, &render_rect);
            } else {
                SDL_RenderCopy(renderer, wall_texture, nullptr, &render_rect);
            }
        }
    }
}

void View::renderScore(int score, const std::string& score_text, int text_y) const {
    // Create surface and texture
    std::string full_text = score_text + std::to_string(score);
    const char* text = (full_text).c_str();
    SDL_Color render_color = {255, 255, 255};
    SDL_Surface* surface_message = TTF_RenderText_Solid(font, text, render_color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface_message);

    int w, h;
    TTF_SizeText(font, text, &w, &h);
    SDL_Rect message_rect = {100, text_y, w, h};
    SDL_RenderCopy(renderer, message, nullptr, &message_rect);
    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(message);
}

void View::renderHealthBar(int center_x, int center_y, double remaining_health, double initial_health) const {
    int bar_x = center_x - Constants::TILE_SIZE;
    int bar_y = center_y - Constants::TILE_SIZE - 5;
    int bar_width = Constants::TILE_SIZE * 2;
    int bar_height = 5;

    // Draw whole bar
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_Rect rect{bar_x, bar_y, bar_width, bar_height};
    SDL_RenderFillRect(renderer, &rect);

    // Draw remaining health
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int remaining_width = static_cast<int>(bar_width * remaining_health / initial_health);

    rect.w = remaining_width;
    SDL_RenderFillRect(renderer, &rect);
}

void View::renderPlayer(const Player& player) const {
    auto [center_x, center_y] = player.getCenter();
    renderHealthBar(static_cast<int>(center_x), static_cast<int>(center_y), player.getHealthPoints(),
                  player.getMaximumHealth());

    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 255);

    std::vector<Position> corner_points = player.getCornerPoints();

    // Find min and max Y to define the scanline range
    int min_y = static_cast<int>(player.getTop());
    int max_y = static_cast<int>(player.getBottom());

    // List of edges pairs of indices in x_points and y_points
    struct Edge {
        double x0, y0, x1, y1;
    };
    std::vector<Edge> edges = {
        {corner_points[0].x, corner_points[0].y, corner_points[1].x, corner_points[1].y},
        {corner_points[1].x, corner_points[1].y, corner_points[2].x, corner_points[2].y},
        {corner_points[2].x, corner_points[2].y, corner_points[3].x, corner_points[3].y},
        {corner_points[3].x, corner_points[3].y, corner_points[0].x, corner_points[0].y},
    };

    for (const Edge& edge: edges) {
        SDL_RenderDrawLine(renderer, static_cast<int>(edge.x0), static_cast<int>(edge.y0), static_cast<int>(edge.x1),
                           static_cast<int>(edge.y1));
    }

    // Scanline fill algorithm
    for (int y = min_y; y <= max_y; ++y) {
        // Iterate from top to bottom (y goes from top to bottom)
        std::vector<int> intersections;

        for (const auto& edge: edges) {
            // Iterate through all edges i.e. all lines between two corners
            int y0 = static_cast<int>(edge.y0);
            int y1 = static_cast<int>(edge.y1);

            // Skip horizontal edges
            if (y0 == y1)
                continue;

            // If y is between the top y and bottom y value, we add an intersection
            // Find x while iterating over y
            if (y >= std::min(y0, y1) && y < std::max(y0, y1)) {
                // Calculate the intersection point
                // (y - y0) / cast(y1 - y0) -> calculate the relative position of y between y0 and y1 in percent
                // Then by multiplying with x1 - x0 we check how far along we are on the vertical axis
                double x = edge.x0 + (edge.x1 - edge.x0) * (static_cast<float>(y - y0)) / static_cast<double>(y1 - y0);
                intersections.push_back(static_cast<int>(x));
            }

            // THe output here are the points on the vertical line between two adjacent vertices of the square
            // We do this per y -> so for each possible y position of the square, we check whether there is an edge
            // between two vertices that have points on this y
            // There are at most 2 of these intersections possible
        }

        // Sort intersections
        std::ranges::sort(intersections);

        // Draw horizontal lines between pairs of intersections
        for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
            int x_start = intersections[i];
            int x_end = intersections[i + 1];

            // Ensure left-to-right drawing
            if (x_start > x_end)
                std::swap(x_start, x_end);

            SDL_RenderDrawLine(renderer, x_start, y, x_end, y);
        }
    }
}

void View::renderProjectiles(const Weapon& weapon) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& projectile: weapon.getProjectiles()) {
        renderCircle(projectile);
        // Position position = projectile.getPosition();
        // auto [x, y] = Position::to_integer(position);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // for (int i = x - 1; i <= x + 1; i++) {
        //     for (int j = y - 1; j <= y + 1; j++) {
        //         SDL_RenderDrawPoint(renderer, i, j);
        //     }
        // }
    }
}

void drawHorizontalLine(SDL_Renderer* renderer, int x1, int x2, int y) {
    for (int x = x1; x <= x2; ++x) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void View::renderCircle(const Circle& circle) const {
    auto [center_x, center_y] = circle.getCenter();
    int cast_x = static_cast<int>(center_x);
    int cast_y = static_cast<int>(center_y);

    auto radius = circle.getRadius();

    int x = 0;
    int y = radius;
    int decision = 1 - radius;
    while (y >= x) {
        // Draw horizontal lines between the points
        drawHorizontalLine(renderer, cast_x - x, cast_x + x, cast_y + y);
        drawHorizontalLine(renderer, cast_x - x, cast_x + x, cast_y - y);
        drawHorizontalLine(renderer, cast_x - y, cast_x + y, cast_y + x);
        drawHorizontalLine(renderer, cast_x - y, cast_x + y, cast_y - x);

        x++;
        if (decision <= 0) {
            decision += 2 * x + 1;
        } else {
            y--;
            decision += 2 * (x - y) + 1;
        }
    }
}

void View::renderLivingCircle(const Circle& circle) const {
    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 255);
    auto [center_x, center_y] = circle.getCenter();
    int cast_x = static_cast<int>(center_x);
    int cast_y = static_cast<int>(center_y);
    renderHealthBar(cast_x, cast_y, circle.getHealthPoints(), circle.getMaximumHealth());
    renderCircle(circle);
}
