//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

constexpr float SPEED = 10.0f;
constexpr int ROTATION_SPEED = 5;

Player::Player(): Rectangle(150.0f, 150.0f) { }

std::pair<float, float> Player::getDeltaPosition(float dpi_scaling) const {
    const float MOVE_INCREMENT = SPEED * dpi_scaling; // Pixels per input event

    const float radians = static_cast<float>(rotation * M_PI) / 180.0f;
    return {
        MOVE_INCREMENT * cos(radians),
        MOVE_INCREMENT * sin(radians)
    };
}

void Player::move(const Grid &grid, float coordinate_scaling, float dpi_scaling) {
    auto [delta_x, delta_y] = getDeltaPosition(dpi_scaling);
    bool collision = false;

    for(int i = 10; i > 0; i--) {
        const float t = static_cast<float>(i) * 0.1f;

        x += t * delta_x;
        y += t * delta_y;
        x_points = calculateXPoints();
        y_points = calculateYPoints();

        int min_x = Grid::toTileCoordinate(this->getLeft());
        int min_y = Grid::toTileCoordinate(this->getTop());
        int max_x = Grid::toTileCoordinate(this->getRight());
        int max_y = Grid::toTileCoordinate(this->getBottom());

        std::cout << "Max y: " << max_y << std::endl;

        for(int i = min_x; i <= max_x; i++) {
            for(int j = min_y; j <= max_y; j++) {
                std::cout << i << " " << j << std::endl;
                const Tile& target_tile = grid.getTile(i, j);
                std::cout << Tile::to_string(target_tile.getTileType()) << std::endl;
                if(target_tile.isNonWalkable()) {
                    collision = true;
                    break;
                }
            }
            if (collision) break;
        }

        if(!collision) {
            break;
        }

        x -= t * delta_x;
        y -= t * delta_y;
        x_points = calculateXPoints();
        y_points = calculateYPoints();
        collision = false;
    }
}

void Player::rotatePlayer(Rotation rotation_type) {
    switch (rotation_type) {
        case RIGHT:
            rotation += ROTATION_SPEED;
            break;
        case LEFT:
            rotation -= ROTATION_SPEED;
            break;
        default:
            break;
    }

    if (rotation > 360) {
        rotation -= 360;
    } else if (rotation < 0) {
        rotation += 360;
    }

    x_points = calculateXPoints();
    y_points = calculateYPoints();
}

std::string Player::to_string(Rotation rotation) {
    switch (rotation) {
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case NONE: return "None";
        default: return "Unknown";
    }
}
