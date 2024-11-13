//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

#include "Constants.hpp"

constexpr float PLAYER_SPEED = 1500.0f;
constexpr int ROTATION_SPEED = 5;
Uint32 lastTime = SDL_GetTicks();

Player::Player(): x_position(150.0f), y_position(150.0f),
                  target_x_position(150), target_y_position(150),
                  player_rotation(0), render(false) {
}

const std::pair<float, float> Player::getPosition() const {
    return {x_position, y_position};
}

std::pair<float, float> Player::getPosition() {
    return {x_position, y_position};
}

const std::pair<float, float> Player::getTargetPosition() const {
    return {target_x_position, target_y_position};
}

std::pair<float, float> Player::getTargetPosition() {
    return {target_x_position, target_y_position};
}

const int Player::getRotationAngle() const {
    return player_rotation;
}

void Player::move(Grid grid) {

    const float radius = 50.0f;
    const float radians = player_rotation * M_PI / 180;
    target_x_position += (radius * cos(radians) / 10);
    target_y_position += (radius * sin(radians) / 10);
}

void Player::finishMove() {
    /*float target_pos_x = target_x_position * Constants::TILE_SIZE;
    float target_pos_y = target_y_position * Constants::TILE_SIZE;*/

    float target_pos_x = x_position + (target_x_position - x_position);
    float target_pos_y = y_position + (target_y_position - y_position);

    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert from ms to seconds
    lastTime = currentTime;
    float adjustedSpeed = PLAYER_SPEED * deltaTime;

    // Move smoothly towards target position
    if (x_position < target_pos_x)
        x_position = std::min(x_position + adjustedSpeed, target_pos_x);
    if (x_position > target_pos_x)
        x_position = std::max(x_position - adjustedSpeed, target_pos_x);
    if (y_position < target_pos_y)
        y_position = std::min(y_position + adjustedSpeed, target_pos_y);
    if (y_position > target_pos_y)
        y_position = std::max(y_position - adjustedSpeed, target_pos_y);
}

void Player::rotatePlayer(Rotation rotation) {
    switch (rotation) {
        case RIGHT:
            player_rotation += ROTATION_SPEED;
            break;
        case LEFT:
            player_rotation -= ROTATION_SPEED;
            break;
        default:
            break;
    }

    if(player_rotation > 360) {
        player_rotation -= 360;
    } else if(player_rotation < 0) {
        player_rotation = player_rotation + 360;
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