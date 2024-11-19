//
// Created by nico on 11/16/24.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

#include "Position.hpp"

class Rectangle {
public:
    Position center;
    float top;
    float bottom;
    float left;
    float right;
    int rotation;
    std::vector<Position> corner_points;


    Rectangle(float x, float y);

    void initialize(Position, int);

    static bool isCollision(const Rectangle&, const Rectangle&);

    [[nodiscard]] const Position& getCenter() const;
    [[nodiscard]] float getTop() const;
    [[nodiscard]] float getBottom() const;
    [[nodiscard]] float getLeft() const;
    [[nodiscard]] float getRight() const;
    [[nodiscard]] const int& getRotation() const;
    [[nodiscard]] const std::vector<Position>& getCornerPoints() const;

    void moveRectangle(Position delta_position, float multiplier);
};

#endif //RECTANGLE_HPP
