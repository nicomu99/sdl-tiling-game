//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

#include "Constants.hpp"

constexpr float PLAYER_SPEED = 300.0f;
Uint32 lastTime = SDL_GetTicks();

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

const std::pair<int, int> Player::getTargetPosition() const {
    return {target_x_position, target_y_position};
}

std::pair<int, int> Player::getTargetPosition() {
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
    //int target_pos_x = target_x_position + dx;
    //int target_pos_y = target_y_position + dy;

    for (int i = 10; i > 0; i--) {
        int target_pos_x = target_x_position + dx * i;
        int target_pos_y = target_y_position + dy * i;
        if (grid.getTile(target_pos_x, target_pos_y) == TileType::Walkable &&
            target_x_position * Constants::TILE_SIZE == x_position &&
            target_y_position * Constants::TILE_SIZE == y_position) {
            target_x_position = target_pos_x;
            target_y_position = target_pos_y;
            return;
        }
    }
}

void Player::finishMove() {
    float target_pos_x = target_x_position * Constants::TILE_SIZE;
    float target_pos_y = target_y_position * Constants::TILE_SIZE;

    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert from ms to seconds
    lastTime = currentTime;
    float adjustedSpeed = PLAYER_SPEED * deltaTime;

    // Move smoothly towards target position
    if (x_position < target_pos_x) x_position = std::min(x_position + adjustedSpeed, target_pos_x);
    if (x_position > target_pos_x) x_position = std::max(x_position - adjustedSpeed, target_pos_x);
    if (y_position < target_pos_y) y_position = std::min(y_position + adjustedSpeed, target_pos_y);
    if (y_position > target_pos_y) y_position = std::max(y_position - adjustedSpeed, target_pos_y);
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
        case LEFTUP:
            return {-1, -1};
        case RIGHTUP:
            return {1, -1};
        case LEFTDOWN:
            return {-1, 1};
        case RIGHTDOWN:
            return {1, 1};
        default:
            return {0, 0};
    }
}
