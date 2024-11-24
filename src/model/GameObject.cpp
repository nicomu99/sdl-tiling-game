//
// Created by nico on 11/22/24.
//
#include "GameObject.hpp"

#include <cmath>

constexpr int ROTATION_SPEED = 300;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;

GameObject::GameObject(): center(0, 0), rotation(0), move_velocity(0, 0), rotation_speed(0), health_points(100.0),
                          has_been_hit(false), maximum_health(100.0), speed(300.0) {
}

GameObject::GameObject(double x, double y): center(x, y), rotation(0), move_velocity(0, 0), rotation_speed(0),
                                            health_points(100.0), has_been_hit(false), maximum_health(100.0), speed(300.0) {
}

GameObject::GameObject(double x, double y, double speed): center(x, y), rotation(0), move_velocity(0, 0), rotation_speed(0),
                                            health_points(100.0), has_been_hit(false), maximum_health(100.0), speed(speed) {
}

GameObject::GameObject(double x, double y,
                       Position move_velocity, double speed): center(x, y), rotation(0),
                                                              move_velocity(move_velocity), rotation_speed(0),
                                                              health_points(100.0), has_been_hit(false), maximum_health(100.0), speed(speed) { }
const Position &GameObject::getCenter() const {
    return center;
}

const int &GameObject::getRotation() const {
    return rotation;
}

const double &GameObject::getHealthPoints() const {
    return health_points;
}

double GameObject::getMaximumHealth() const {
    return maximum_health;
}

bool GameObject::isDead() const {
    return health_points <= 0;
}

void GameObject::setVelocity(Position &move_velocity) {
    this->move_velocity = move_velocity;
}

void GameObject::setRotation(Rotation rotation) {
    this->rotation_speed = static_cast<int>(rotation);
}

void GameObject::setHasBeenHit(bool) {
    this->has_been_hit = true;
    health_points -= 10;
}

void GameObject::calculateRotationWithTarget(Position target_position) {
    Position relative_position = target_position - this->center;
    double theta = atan2(relative_position.y, relative_position.x);
    double rotation_radians = rotation * M_PI / 180;
    double phi = theta - rotation_radians;

    rotation += static_cast<int>(phi * 180 / M_PI);
    rotation = (rotation + 360) % 360;
}

Position GameObject::calculateTrajectory() const {
    const double radians = static_cast<double>(rotation) * M_PI / 180.0;
    return {
        cos(radians),
        sin(radians)
    };
}

void GameObject::performMove(Position position, double delta_time, double multiplier) {
    const double MOVE_INCREMENT = speed * delta_time;
    center += position * MOVE_INCREMENT * move_velocity * multiplier;
}

void GameObject::move(const Grid &grid, double delta_time) {
    auto [delta_x, delta_y] = calculateTrajectory();

    for (int step = MAX_STEPS; step > 0; step--) {
        const double t = static_cast<double>(step) * STEP_SIZE;
        Position delta_position(delta_x * t, delta_y * t);
        performMove(delta_position, delta_time, 1);

        if (checkGridCollision(grid)) {
            // Reset the rectangle position if a collision was detected
            performMove(delta_position, -1, -1);
        } else {
            break;
        }
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
