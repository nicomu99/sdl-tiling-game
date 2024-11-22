//
// Created by nico on 11/22/24.
//
#include "Circle.hpp"

constexpr int MAX_STEPS = 10;
constexpr double STEP_SIZE = 1.0 / MAX_STEPS;

Circle::Circle(): GameObject(0, 0), radius(0) { }

Circle::Circle(double x, double y): GameObject(x, y), radius(10) { }

bool Circle::checkGridCollision(const Grid& grid) const {
    int min_x = Grid::toTileCoordinate(center.x - radius);
    int min_y = Grid::toTileCoordinate(center.y - radius);
    int max_x = Grid::toTileCoordinate(center.x + radius);
    int max_y = Grid::toTileCoordinate(center.y + radius);
    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {
            const Tile& target_tile = grid.getTile(i, j);
            if(target_tile.isNonWalkable()) {
                return true;
            }
        }
    }
    return false;
}

void Circle::initialize(Position, int) { }

const int& Circle::getRadius() const {
    return radius;
}

