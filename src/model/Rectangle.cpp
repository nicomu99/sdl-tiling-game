//
// Created by nico on 11/16/24.
//
#include "Rectangle.hpp"

#include <cmath>
#include <ios>
#include <vector>
#include <algorithm>

#include "Constants.hpp"

constexpr float HALF_LENGTH = Constants::TILE_SIZE / 2.0f;

Rectangle::Rectangle(float x, float y): center(x, y), top(0.0f), bottom(0.0f),
                                        left(0.0f), right(0.0f), rotation(0) {
    initialize(center, rotation);
}

void Rectangle::initialize(Position center, int rotation) {
    corner_points.clear();

    std::vector<Position> corners = {
        {-HALF_LENGTH, -HALF_LENGTH},
        {HALF_LENGTH, -HALF_LENGTH},
        {HALF_LENGTH, HALF_LENGTH},
        {-HALF_LENGTH, HALF_LENGTH}
    };

    const double radians = rotation * M_PI / 180.0f;
    const auto cos_a = static_cast<float>(cos(radians));
    const auto sin_a = static_cast<float>(sin(radians));

    bottom = 0;
    top = Constants::SCREEN_HEIGHT;
    left = Constants::SCREEN_WIDTH;
    right = 0;
    for (const auto& point : corners) {
        float corner_x = center.x + point.x * cos_a - point.y * sin_a;
        float corner_y = center.y + point.x * sin_a + point.y * cos_a;

        left = std::min(left, corner_x);
        right = std::max(right, corner_x);
        top = std::min(top, corner_y);
        bottom = std::max(bottom, corner_y);

        corner_points.emplace_back(corner_x, corner_y);
    }
}

bool Rectangle::isCollision(const Rectangle &r1, const Rectangle &r2) {
    return r1.getTop() > r2.getBottom() || r1.getBottom() < r2.getTop() || r1.getLeft() < r2.getRight() || r1.getRight()
           > r2.getLeft();
}

const Position& Rectangle::getCenter() const {
    return center;
}

float Rectangle::getTop() const {
    return top;
}

float Rectangle::getBottom() const {
    return bottom;
}


float Rectangle::getLeft() const {
    return left;
}

float Rectangle::getRight() const {
    return right;
}

const int &Rectangle::getRotation() const {
    return rotation;
}

const std::vector<Position> & Rectangle::getCornerPoints() const {
    return corner_points;
}

void Rectangle::moveRectangle(Position delta_position, float multiplier) {
    center += delta_position * multiplier;
    initialize(center, rotation);
}
