//
// Created by nico on 11/9/24.
//
#include "View.hpp"

#include <algorithm>
#include <iostream>

#include "Constants.hpp"

View::View(const SDLManager& sdl_manager): renderer(sdl_manager.getRenderer()) { }

void View::render(const Model& model, float coordinate_scaling) const {
    renderTileMap(model.getGrid());
    renderPlayer(model.getPlayer(), coordinate_scaling);
    renderProjectiles(model.getPlayer().getWeapon());
    SDL_RenderPresent(renderer);
}

void View::renderTileMap(const Grid& grid) const {
    const std::vector<std::vector<Tile>>& tile_map = grid.getTileMap();
    for(const auto & i : tile_map) {
        for(const auto& tile : i) {
            if(tile.getTileType() == TileType::Walkable) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_Rect render_rect = {static_cast<int>(tile.getLeft()), static_cast<int>(tile.getTop()), Constants::TILE_SIZE, Constants::TILE_SIZE};
            SDL_RenderFillRect(renderer, &render_rect);
        }
    }
}

void View::renderPlayer(const Player& player, float coordinate_scaling) const {
    std::vector<Position> corner_points = player.getCornerPoints();

    // Find min and max Y to define the scanline range
    int min_y = static_cast<int>(player.getTop());
    int max_y = static_cast<int>(player.getBottom());

    // List of edges pairs of indices in x_points and y_points
    struct Edge {
        float x0, y0, x1, y1;
    };
    std::vector<Edge> edges = {
        {corner_points[0].x, corner_points[0].y, corner_points[1].x, corner_points[1].y},
        {corner_points[1].x, corner_points[1].y, corner_points[2].x, corner_points[2].y},
        {corner_points[2].x, corner_points[2].y, corner_points[3].x, corner_points[3].y},
        {corner_points[3].x, corner_points[3].y, corner_points[0].x, corner_points[0].y},
    };

    // Scanline fill algorithm
    for (int y = min_y; y <= max_y; ++y) {
        // Iterate from top to bottom (y goes from top to bottom)
        std::vector<int> intersections;

        for (const auto& edge : edges) {
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
    for(auto projectile: weapon.getProjectiles()) {
        Position position = projectile.getPosition();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, static_cast<int>(position.x), static_cast<int>(position.y));
    }
}
