//
// Created by nico on 11/16/24.
//
#include "Rectangle.hpp"

#include <cmath>
#include <ios>
#include <vector>
#include <algorithm>

#include "Constants.hpp"
#include "Grid.hpp"


Rectangle::Rectangle(double x, double y, double speed): GameObject(x, y, speed), top(0.0), bottom(0.0),
                                        left(0.0), right(0.0) {
    Rectangle::initialize(center, rotation);
}

void Rectangle::initialize(Position center, int rotation) {
    corner_points.clear();

    constexpr double HALF_LENGTH = Constants::TILE_SIZE / 2.0;
    std::vector<Position> corners = {
        {-HALF_LENGTH, -HALF_LENGTH},
        {HALF_LENGTH, -HALF_LENGTH},
        {HALF_LENGTH, HALF_LENGTH},
        {-HALF_LENGTH, HALF_LENGTH}
    };

    const double radians = rotation * M_PI / 180.0f;
    const auto cos_a = cos(radians);
    const auto sin_a = sin(radians);

    bottom = 0;
    top = Constants::SCREEN_HEIGHT;
    left = Constants::SCREEN_WIDTH;
    right = 0;
    for (const auto& point : corners) {
        double corner_x = center.x + point.x * cos_a - point.y * sin_a;
        double corner_y = center.y + point.x * sin_a + point.y * cos_a;

        left = std::min(left, corner_x);
        right = std::max(right, corner_x);
        top = std::min(top, corner_y);
        bottom = std::max(bottom, corner_y);

        corner_points.emplace_back(corner_x, corner_y);
    }
}

double Rectangle::getTop() const {
    return top;
}

double Rectangle::getBottom() const {
    return bottom;
}


double Rectangle::getLeft() const {
    return left;
}

double Rectangle::getRight() const {
    return right;
}

const std::vector<Position> & Rectangle::getCornerPoints() const {
    return corner_points;
}

