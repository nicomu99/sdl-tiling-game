//
// Created by nico on 11/18/24.
//

#ifndef POINT_HPP
#define POINT_HPP
#include <string>

struct Position {
    float x;
    float y;

    Position(float x, float y): x(x), y(y) { }

    Position& operator+=(const Position& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position operator+(const Position& other) const {
        return {x + other.x, y + other.y};
    }

    Position& operator*(const float& multiplier) {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }

    static std::string to_string(Position position) {
        return std::to_string(position.x) + " " + std::to_string(position.y);
    }
};

#endif //POINT_HPP
