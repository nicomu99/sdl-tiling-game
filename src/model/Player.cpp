//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

constexpr float SPEED = 300.0f;
constexpr int ROTATION_SPEED = 5;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;
Uint32 last_update = SDL_GetTicks();

Player::Player(): Rectangle(150.0f, 150.0f), weapon(Weapon()), move_velocity(0, 0) { }

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

void Player::setVelocity(Position& move_velocity) {
    this->move_velocity = move_velocity;
}

void Player::move(const Grid &grid, float delta_time) {
    Uint32 dt = SDL_GetTicks() - last_update;
    const float MOVE_INCREMENT = SPEED * static_cast<float>(dt) / 1000.0f;
    auto [delta_x, delta_y] = getDeltaPosition(MOVE_INCREMENT);

    for(int step = MAX_STEPS; step > 0; step--) {
        const float t = static_cast<float>(step) * STEP_SIZE;
        Position delta_position(delta_x * t * move_velocity.x, delta_y * t * move_velocity.y);
        moveRectangle(delta_position, 1);

        if(checkGridCollision(grid)) {
            // Reset the rectangle position if a collision was detected
            moveRectangle(delta_position, -1);
        } else {
            break;
        }
    }

    last_update = SDL_GetTicks();
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
    move(grid, 0.0f);
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
