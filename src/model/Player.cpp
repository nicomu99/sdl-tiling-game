//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

constexpr float SPEED = 10.0f;
constexpr int ROTATION_SPEED = 5;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;

Player::Player(): Rectangle(150.0f, 150.0f) { }

std::pair<float, float> Player::getDeltaPosition(float dpi_scaling) const {
    const float MOVE_INCREMENT = SPEED * dpi_scaling; // Pixels per input event

    const float radians = static_cast<float>(rotation * M_PI) / 180.0f;
    return {
        MOVE_INCREMENT * cos(radians),
        MOVE_INCREMENT * sin(radians)
    };
}

bool Player::checkGridCollision(const Grid& grid) const {
    int min_x = Grid::toTileCoordinate(this->getLeft());
    int min_y = Grid::toTileCoordinate(this->getTop());
    int max_x = Grid::toTileCoordinate(this->getRight());
    int max_y = Grid::toTileCoordinate(this->getBottom());
    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {
            const Tile& target_tile = grid.getTile(i, j);
            if(target_tile.isNonWalkable() && isCollision(*this, target_tile)) {
                return true;
            }
        }
    }
    return false;
}

void Player::move(const Grid &grid, float coordinate_scaling, float dpi_scaling) {
    auto [delta_x, delta_y] = getDeltaPosition(dpi_scaling);

    for(int step = MAX_STEPS; step > 0; step--) {
        const float t = static_cast<float>(step) * STEP_SIZE;
        moveRectangle(t * delta_x, t * delta_y, 1);

        if(checkGridCollision(grid)) {
            // Reset the rectangle position if a collision was detected
            moveRectangle(t * delta_x, t * delta_y, -1);
        } else {
            break;
        }
    }
}

void Player::rotatePlayer(Rotation rotation_type, const Grid& grid) {
    rotation += rotation_type * ROTATION_SPEED;
    rotation = (rotation % 360 + 360) % 360;
    x_points = calculateXPoints();
    y_points = calculateYPoints();

    if(checkGridCollision(grid)) {
        rotation -= rotation_type * ROTATION_SPEED;
        rotation = (rotation % 360 + 360) % 360;
        x_points = calculateXPoints();
        y_points = calculateYPoints();
    }
}

std::string Player::to_string(Rotation rotation) {
    switch (rotation) {
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case NONE: return "None";
        default: return "Unknown";
    }
}
