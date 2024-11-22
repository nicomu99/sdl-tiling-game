//
// Created by nico on 11/22/24.
//
#include "Circle.hpp"

constexpr int MAX_STEPS = 10;
constexpr double STEP_SIZE = 1.0 / MAX_STEPS;

Circle::Circle(): GameObject(0, 0), radius(0) { }

Circle::Circle(double x, double y): GameObject(x, y), radius(10) { }

bool Circle::checkGridCollision(const Grid& grid) const {
    return true;
}

void Circle::initialize(Position, int) { }

const int& Circle::getRadius() const {
    return radius;
}

