//
// Created by nico on 11/22/24.
//
#include "Circle.hpp"

#include "Grid.hpp"
#include "Tile.hpp"

Circle::Circle(): GameObject(0, 0), radius(0) { }

Circle::Circle(double x, double y): GameObject(x, y), radius(15) { }

Circle::Circle(double x, double y, double speed, int radius): GameObject(x, y, Position(1, 1), speed), radius(radius)  { }

Circle::Circle(double x, double y, Position move_velocity, double speed): GameObject(x, y, move_velocity, speed), radius(15) { }

void Circle::initialize(Position, int) { }

const int& Circle::getRadius() const {
    return radius;
}

