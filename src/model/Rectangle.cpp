//
// Created by nico on 11/16/24.
//
#include "Rectangle.hpp"

#include <cmath>
#include <ios>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Constants.hpp"

constexpr float HALF_LENGTH = Constants::TILE_SIZE / 2.0f;


Rectangle::Rectangle(float x, float y): x(x), y(y), rotation(0), x_points(calculateXPoints()), y_points(calculateYPoints()) {
}

/// This function calculates the edge coordinates of the rectangle, if the rectangle has a rotation of 0.
/// @param center One of the center coordinates of the rectangle
/// @param multiplier Multiplier indicating which corner we are calculating -1 for left and top, 1 for bottom and right
/// @return
float Rectangle::computeCorners(float center, float multiplier) {
    return center + multiplier * static_cast<float>(Constants::TILE_SIZE) / 2;
}

std::vector<int> Rectangle::calculateXPoints() const {
    const double radians = rotation * M_PI / 180.0f;
    const auto cos_a = static_cast<float>(cos(radians));
    const auto sin_a = static_cast<float>(sin(radians));

    const float x_offsets[4] = {-HALF_LENGTH, HALF_LENGTH, HALF_LENGTH, -HALF_LENGTH};
    const float y_offsets[4] = {-HALF_LENGTH, -HALF_LENGTH, HALF_LENGTH, HALF_LENGTH};

    std::vector<int> x_points(4);
    for (int i = 0; i < 4; ++i) {
        x_points[i] = static_cast<int>(x + x_offsets[i] * cos_a - y_offsets[i] * sin_a);
    }

    return x_points;
}

std::vector<int> Rectangle::calculateYPoints() const {
    const double radians = rotation * M_PI / 180.0f;
    const auto cos_a = static_cast<float>(cos(radians));
    const auto sin_a = static_cast<float>(sin(radians));

    const float x_offsets[4] = {-HALF_LENGTH, HALF_LENGTH, HALF_LENGTH, -HALF_LENGTH};
    const float y_offsets[4] = {-HALF_LENGTH, -HALF_LENGTH, HALF_LENGTH, HALF_LENGTH};

    std::vector<int> y_points(4);
    for (int i = 0; i < 4; ++i) {
        y_points[i] = static_cast<int>(y + x_offsets[i] * sin_a + y_offsets[i] * cos_a);
    }

    return y_points;
}

const std::vector<int>& Rectangle::getXPoints() const {
    return x_points;
}

const std::vector<int>& Rectangle::getYPoints() const {
    return y_points;
}

bool Rectangle::isCollision(const Rectangle &r1, const Rectangle &r2) {
    std::cout << r1.getLeft() << " " << r2.getRight() << std::endl;
    return r1.getTop() > r2.getBottom() && r1.getBottom() < r2.getTop() && r1.getLeft() > r2.getRight() && r1.getRight() < r2.getLeft();
}

const float &Rectangle::getX() const {
    return x;
}

const float &Rectangle::getY() const {
    return y;
}

float Rectangle::getTop() const {
    return static_cast<float>(*std::ranges::min_element(y_points));
}

float Rectangle::getBottom() const {
    return static_cast<float>(*std::ranges::max_element(y_points));
}


float Rectangle::getLeft() const {
    return static_cast<float>(*std::ranges::min_element(x_points));
}

float Rectangle::getRight() const {
    return static_cast<float>(*std::ranges::max_element(x_points));
}

const int& Rectangle::getRotation() const {
    return rotation;
}
