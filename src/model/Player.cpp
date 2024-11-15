//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <iostream>
#include <SDL_timer.h>

constexpr float SPEED = 10.0f;
constexpr int ROTATION_SPEED = 5;

Player::Player(): x_position(150.0f), y_position(150.0f),
                  target_x_position(150), target_y_position(150),
                  player_rotation(0), render(false) {
}

std::pair<float, float> Player::getPosition() const {
    return {x_position, y_position};
}

std::pair<float, float> Player::getTargetPosition() const {
    return {target_x_position, target_y_position};
}

int Player::getRotationAngle() const {
    return player_rotation;
}

std::pair<float, float> Player::getDeltaPosition(float dpi_scaling) {
    float MOVE_INCREMENT = SPEED * dpi_scaling; // Pixels per input event

    const float radians = static_cast<float>(player_rotation * M_PI) / 180.0f;
    return {
        MOVE_INCREMENT * cos(radians),
        MOVE_INCREMENT * sin(radians)
    };
}

void Player::move(const Grid &grid, float coordinate_scaling, float dpi_scaling) {
    auto [delta_x, delta_y] = getDeltaPosition(dpi_scaling);
    x_position += delta_x;
    y_position += delta_y;
}

void Player::finishMove(float coordinate_scaling) {
    // Calculate movement in pixels
    float pixels_to_move = SPEED * coordinate_scaling;

    // Calculate the distance to the target position
    float dx = target_x_position - x_position;
    float dy = target_y_position - y_position;
    float distance_to_target = sqrt(dx * dx + dy * dy);

    // If the distance is less than or equal to the movement, snap to target
    if (distance_to_target <= pixels_to_move) {
        x_position = target_x_position;
        y_position = target_y_position;
    } else {
        // Move towards the target position
        float ratio = pixels_to_move / distance_to_target;
        x_position += dx * ratio;
        y_position += dy * ratio;
    }
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

    if (player_rotation > 360) {
        player_rotation -= 360;
    } else if (player_rotation < 0) {
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
