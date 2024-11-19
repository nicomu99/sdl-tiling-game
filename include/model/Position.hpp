//
// Created by nico on 11/18/24.
//

#ifndef POINT_HPP
#define POINT_HPP

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
};

#endif //POINT_HPP
