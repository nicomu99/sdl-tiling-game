//
// Created by nico on 11/9/24.
//
#include "View.hpp"

#include <algorithm>
#include <iostream>

#include "Constants.hpp"

View::View(SDLManager& sdl_manager): renderer(sdl_manager.getRenderer()) { }

void View::render(const Model& model) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const std::vector<std::vector<TileType>>& grid = model.getGrid().getTileMap();
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == TileType::Walkable) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            SDL_Rect render_rect = {Constants::TILE_SIZE * j, Constants::TILE_SIZE * i, Constants::TILE_SIZE, Constants::TILE_SIZE};
            SDL_RenderFillRect(renderer, &render_rect);
        }
    }

    renderPlayer(model.getPlayer());

    SDL_RenderPresent(renderer);
}

std::pair<int, int> calculateCorner(int center_x, int center_y, float x, float y, float angle) {
    return {
        center_x + (x * cos(angle) - y * sin(angle)),
        center_y + (x * sin(angle) + y * cos(angle))
    };
}

float getPointOnLine(float slope, float d, int x) {
    return static_cast<float>(x)*slope + d;
}

void View::drawLine(int x1, int y1, int x2, int y2) {
    if(x2 != x1) {
        float slope = (static_cast<float>(y2) - static_cast<float>(y1))/(static_cast<float>(x2) - static_cast<float>(x1));
        int d = y1 - slope * x1;
        for (int i = x1; i < x2; i++) {
            float y = getPointOnLine(slope, d, i);
            int rounded_y = static_cast<int>(std::round(y));
            SDL_RenderDrawPoint(renderer, i, rounded_y);
        }
    } else {
        int lower_y = y1;
        int upper_y = y2;
        if (y1 > y2) {
            lower_y = y2;
            upper_y = y1;
        }
        for (int i = lower_y; i <= upper_y; i++) {
            SDL_RenderDrawPoint(renderer, x1, i);
        }
    }

}

// Helper function to interpolate between two points (x1, y1) and (x2, y2) for a given y
int interpolateX(int x1, int y1, int x2, int y2, int y) {
    if (y2 == y1) return x1; // Prevent division by zero
    return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
}


void View::renderPlayer(const Player& player) {
    auto [current_x, current_y] = player.getPosition();

    // Rectangle center point
    double rect_center_x = current_x + Constants::TILE_SIZE / 2.0f;
    double rect_center_y = current_y + Constants::TILE_SIZE / 2.0f;
    double half_length = Constants::TILE_SIZE / 2.0f;

    // Rotation angle in degrees and radians
    double degrees = player.getRotationAngle();
    double radians = degrees * M_PI / 180.0;
    double cos_a = cos(radians);
    double sin_a = sin(radians);

    // Calculate the four corners of the rotated rectangle
    double x_offsets[4] = {-half_length, half_length, half_length, -half_length};
    double y_offsets[4] = {-half_length, -half_length, half_length, half_length};

    std::vector<int> x_points(4);
    std::vector<int> y_points(4);
    for (int i = 0; i < 4; ++i) {
        double dx = x_offsets[i];
        double dy = y_offsets[i];

        // Rotate point around the center
        double x_rot = dx * cos_a - dy * sin_a;
        double y_rot = dx * sin_a + dy * cos_a;

        x_points[i] = static_cast<int>(rect_center_x + x_rot);
        y_points[i] = static_cast<int>(rect_center_y + y_rot);
    }

    // Find min and max Y to define the scanline range
    int min_y = *std::ranges::min_element(y_points);
    int max_y = static_cast<int>(std::ceil(*std::ranges::max_element(y_points)));

    // List of edges pairs of indices in x_points and y_points
    struct Edge {
        int x0, y0, x1, y1;
    };
    std::vector<Edge> edges = {
        {x_points[0], y_points[0], x_points[1], y_points[1]},
        {x_points[1], y_points[1], x_points[2], y_points[2]},
        {x_points[2], y_points[2], x_points[3], y_points[3]},
        {x_points[3], y_points[3], x_points[0], y_points[0]},
    };

    // Scanline fill algorithm
    for (int y = min_y; y <= max_y; ++y) {
        // Iterate from top to bottom (y goes from top to bottom)
        std::vector<int> intersections;

        for (const auto& edge : edges) {
            // Iterate through all edges i.e. all lines between two corners
            int y0 = edge.y0;
            int y1 = edge.y1;

            // Skip horizontal edges
            if (y0 == y1)
                continue;

            // If y is between the top y and bottom y value, we add an intersection
            // Find x while iterating over y
            if (y >= std::min(y0, y1) && y < std::max(y0, y1)) {
                // Calculate the intersection point
                // (y - y0) / cast(y1 - y0) -> calcualte the relative position of y between y0 and y1 in percent
                // Then by multiplying with x1 - x0 we check how far along we are on the vertical axis
                double x = edge.x0 + (edge.x1 - edge.x0) * (y - y0) / static_cast<double>(y1 - y0);
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
