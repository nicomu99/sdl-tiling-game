//
// Created by nico on 11/18/24.
//

#ifndef POINT_HPP
#define POINT_HPP
#include <string>

struct Position {
    double x;
    double y;

    Position(double x, double y): x(x), y(y) {
    }

    Position &operator+=(const Position &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position operator+(const Position &other) const {
        return {x + other.x, y + other.y};
    }

    Position &operator*(const double &multiplier) {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }

    Position operator*(const Position& other) const {
        return {x * other.x, y * other.y};
    }

    static std::string to_string(Position position) {
        return std::to_string(position.x) + " " + std::to_string(position.y);
    }

    static std::pair<int, int> to_integer(Position position) {
        return {
            static_cast<int>(position.x),
            static_cast<int>(position.y)
        };
    }
};

inline Position operator*(float multiplier, const Position& obj) {
    return Position{obj.x * multiplier, obj.y * multiplier};
}

#endif //POINT_HPP
