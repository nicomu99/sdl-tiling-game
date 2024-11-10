//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

#include "Constants.hpp"

constexpr float PLAYER_SPEED = 10.0f;

Player::Player(): x_position(40.0f), y_position(40.0f), move_direction(NONE),
                  target_x_position(40 / Constants::TILE_SIZE), target_y_position(40 / Constants::TILE_SIZE),
                  render(false) {
}

Player::Player(int x_position, int y_position): x_position(x_position), y_position(y_position),
                                                move_direction(NONE),
                                                target_x_position(x_position / Constants::TILE_SIZE),
                                                target_y_position(y_position / Constants::TILE_SIZE), render(false) {
}

const std::pair<float, float> Player::getPosition() const {
    return {x_position, y_position};
}

std::pair<float, float> Player::getPosition() {
    return {x_position, y_position};
}

const std::pair<float, float> Player::getPreviousPosition() const {
    return {target_x_position, target_y_position};
}

std::pair<float, float> Player::getPreviousPosition() {
    return {target_x_position, target_y_position};
}

Player::Direction Player::getDirection() {
    return move_direction;
}

const Player::Direction Player::getDirection() const {
    return move_direction;
}

void Player::move(Direction direction, Grid grid) {
    move_direction = direction;

    auto [dx, dy] = toPair(direction);
    int target_pos_x = target_x_position + dx;
    int target_pos_y = target_y_position + dy;

    if(grid.getTile(target_x_position, target_y_position) == TileType::Walkable) {
        std::cout << "Walkable" << std::endl;
    } else {
        std::cout << "NonWalkable" << std::endl;
    }

    if (grid.getTile(target_pos_x, target_pos_y) == TileType::Walkable) {
        target_x_position = target_pos_x;
        target_y_position = target_pos_y;
    }
}

void Player::finishMove() {
    float target_pos_x = target_x_position * Constants::TILE_SIZE;
    float target_pos_y = target_y_position * Constants::TILE_SIZE;

    // Move smoothly towards target position
    if (x_position < target_pos_x) x_position = std::min(x_position + PLAYER_SPEED, target_pos_x);
    if (x_position > target_pos_x) x_position = std::max(x_position - PLAYER_SPEED, target_pos_x);
    if (y_position < target_pos_y) y_position = std::min(y_position + PLAYER_SPEED, target_pos_y);
    if (y_position > target_pos_y) y_position = std::max(y_position - PLAYER_SPEED, target_pos_y);
}

// Converts a direction to a coordinate pair
std::pair<int, int> Player::toPair(Direction dir) {
    switch (dir) {
        case UP:
            return {0, -1};
        case DOWN:
            return {0, 1};
        case LEFT:
            return {-1, 0};
        case RIGHT:
            return {1, 0};
        default:
            return {0, 0};
    }
}
