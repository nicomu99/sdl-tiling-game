//
// Created by nico on 11/16/24.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

#include "Position.hpp"
#include "GameObject.hpp"

class Grid;

class Rectangle : public GameObject {
    double top;
    double bottom;
    double left;
    double right;
    std::vector<Position> corner_points;

public:
    Rectangle(double x, double y, double speed);

    void initialize(Position, int) override;

    [[nodiscard]] double getTop() const;
    [[nodiscard]] double getBottom() const;
    [[nodiscard]] double getLeft() const;
    [[nodiscard]] double getRight() const;
    [[nodiscard]] const std::vector<Position>& getCornerPoints() const;
};

#endif //RECTANGLE_HPP
