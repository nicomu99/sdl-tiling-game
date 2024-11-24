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

constexpr float HALF_LENGTH = Constants::TILE_SIZE / 2.0f;

Rectangle::Rectangle(double x, double y): GameObject(x, y, 400.0), top(0.0f), bottom(0.0f),
                                        left(0.0f), right(0.0f) {
    Rectangle::initialize(center, rotation);
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

bool Rectangle::isCollision(const Rectangle &r1, const Rectangle &r2) {
    return r1.getTop() > r2.getBottom() || r1.getBottom() < r2.getTop() || r1.getLeft() < r2.getRight() || r1.getRight()
           > r2.getLeft();
}

bool Rectangle::checkGridCollision(const Grid& grid) const {
    int min_x = Grid::toTileCoordinate(this->getLeft());
    int min_y = Grid::toTileCoordinate(this->getTop());
    int max_x = Grid::toTileCoordinate(this->getRight());
    int max_y = Grid::toTileCoordinate(this->getBottom());
    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {
            const Tile& target_tile = grid.getTile(i, j);
            if(target_tile.isNonWalkable() && isCollision(*this, target_tile)) {
                return true;
            }
        }
    }
    return false;
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

