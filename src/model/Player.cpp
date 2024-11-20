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

Player::Player(): Rectangle(150.0f, 150.0f), weapon(Weapon()) { }

Position Player::getDeltaPosition(float multiplier) const {
    const float radians = static_cast<float>(rotation * M_PI) / 180.0f;
    return {
        multiplier * cos(radians),
        multiplier * sin(radians)
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

const Weapon & Player::getWeapon() const {
    return weapon;
}

Weapon& Player::getWeapon() {
    return weapon;
}

void Player::move(const Grid &grid, float coordinate_scaling) {
    const float MOVE_INCREMENT = SPEED;
    auto [delta_x, delta_y] = getDeltaPosition(MOVE_INCREMENT);

    for(int step = MAX_STEPS; step > 0; step--) {
        const float t = static_cast<float>(step) * STEP_SIZE;
        Position delta_position(delta_x * t, delta_y * t);
        moveRectangle(delta_position, 1);

        if(checkGridCollision(grid)) {
            // Reset the rectangle position if a collision was detected
            moveRectangle(delta_position, -1);
        } else {
            break;
        }
    }
}

void Player::rotatePlayer(Rotation rotation_type, const Grid& grid) {
    int new_rotation = rotation + rotation_type * ROTATION_SPEED;
    new_rotation = (new_rotation % 360 + 360) % 360;
    initialize(center, new_rotation);

    if(!checkGridCollision(grid)) {
        rotation = new_rotation;
    } else {
        initialize(center, rotation);
    }
}

void Player::fireWeapon() {
    Position delta_position = getDeltaPosition(1);
    weapon.fireWeapon(center, delta_position);
}

void Player::update(const Grid& grid) {
    weapon.updateBullets(grid);
}

std::string Player::to_string(Rotation rotation) {
    switch (rotation) {
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case NONE: return "None";
        default: return "Unknown";
    }
}
