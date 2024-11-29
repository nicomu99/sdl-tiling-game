//
// Created by nico on 11/22/24.
//
#include "GameObject.hpp"

#include <cmath>
#include <iostream>

#include "Constants.hpp"

constexpr int ROTATION_SPEED = 300;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;

GameObject::GameObject()
    : center(0, 0), rotation(0), move_velocity(0, 0), rotation_speed(0), health_points(100.0),
      has_been_hit(false), maximum_health(100.0), speed(300.0) {
}

GameObject::GameObject(double x, double y)
    : center(x, y), rotation(0), move_velocity(0, 0), rotation_speed(0),
      health_points(100.0), has_been_hit(false), maximum_health(100.0),
      speed(Constants::PLAYER_SPEED) {
}

GameObject::GameObject(double x, double y, double speed)
    : center(x, y), rotation(0), move_velocity(0, 0),
      rotation_speed(0),
      health_points(100.0), has_been_hit(false),
      maximum_health(100.0), speed(speed) {
}

GameObject::GameObject(double x, double y,
                       Position move_velocity, double speed)
    : center(x, y), rotation(0),
      move_velocity(move_velocity), rotation_speed(0),
      health_points(100.0), has_been_hit(false),
      maximum_health(100.0), speed(speed) {
}

const Position& GameObject::getCenter() const {
    return center;
}

const int& GameObject::getRotation() const {
    return rotation;
}

const double& GameObject::getHealthPoints() const {
    return health_points;
}

double GameObject::getMaximumHealth() const {
    return maximum_health;
}

bool GameObject::isDead() const {
    return health_points <= 0;
}

void GameObject::setVelocity(Position& move_velocity) {
    if (!has_been_hit) {
        this->move_velocity = move_velocity;
    }
}

void GameObject::calculateRotationWithTarget(Position target_position) {
    // if (!has_been_hit) {
        Position relative_position = target_position - this->center;
        double theta = atan2(relative_position.y, relative_position.x);
        double rotation_radians = rotation * M_PI / 180;
        double phi = theta - rotation_radians;

        rotation += static_cast<int>(phi * 180 / M_PI);
        rotation = (rotation + 360) % 360;
    // }
}

Position GameObject::calculateTrajectory() const {
    const double radians = static_cast<double>(rotation) * M_PI / 180.0;
    return {
        cos(radians),
        sin(radians)
    };
}

Position GameObject::calculateDeltaPosition() {
    if (!has_been_hit) {
        return calculateTrajectory();
    }

    recoil_counter--;
    if(recoil_counter < 0) {
        afterCollision();
    }
    return {1, 1};
}

void GameObject::performMove(Position delta_position, double delta_time) {
    center += delta_position * speed * delta_time * move_velocity;
}

void GameObject::move(double delta_time, double multiplier) {
    Position delta_position = calculateDeltaPosition();
    performMove(delta_position, delta_time);
}
