//
// Created by nico on 11/22/24.
//
#include "GameObject.hpp"

#include <cmath>
#include <iostream>

constexpr double SPEED = 300.0;
constexpr int ROTATION_SPEED = 200;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;

GameObject::GameObject(): center(0, 0), rotation(0), move_velocity(0, 0), rotation_speed(0), health_points(100.0), has_been_hit(false), maximum_health(100.0) {
}

GameObject::GameObject(double x, double y): center(x, y), rotation(0), move_velocity(0, 0), rotation_speed(0), health_points(100.0), has_been_hit(false), maximum_health(100.0) { }

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
    this->move_velocity = move_velocity;
}

void GameObject::setRotation(Rotation rotation) {
    this->rotation_speed = static_cast<int>(rotation);
}

void GameObject::setHasBeenHit(bool) {
    this->has_been_hit = true;
    health_points -= 10;
    std::cout << health_points << std::endl;
}

Position GameObject::calculateTrajectory(double multiplier) const {
    const double radians = static_cast<double>(rotation) * M_PI / 180.0;
    return {
        multiplier * cos(radians),
        multiplier * sin(radians)
    };
}

void GameObject::performMove(Position position, double i) {
    center += position * i;
}

void GameObject::move(const Grid &grid, double delta_time) {
    const double MOVE_INCREMENT = SPEED * delta_time;
    auto [delta_x, delta_y] = calculateTrajectory(MOVE_INCREMENT);

    for(int step = MAX_STEPS; step > 0; step--) {
        const double t = static_cast<double>(step) * STEP_SIZE;
        Position delta_position(delta_x * t * move_velocity.x, delta_y * t * move_velocity.y);
        performMove(delta_position, 1);

        if(checkGridCollision(grid)) {
            // Reset the rectangle position if a collision was detected
            performMove(delta_position, -1);
        } else {
            break;
        }
    }
}

void GameObject::rotateGameObject(const Grid& grid, double delta_time) {
    int new_rotation = rotation + rotation_speed * ROTATION_SPEED * delta_time;
    new_rotation = (new_rotation % 360 + 360) % 360;
    initialize(center, new_rotation);

    if(!checkGridCollision(grid)) {
        rotation = new_rotation;
    } else {
        initialize(center, rotation);
    }
}

std::string GameObject::to_string(Rotation rotation) {
    switch (rotation) {
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case NONE: return "None";
        default: return "Unknown";
    }
}
