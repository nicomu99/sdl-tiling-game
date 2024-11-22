//
// Created by nico on 11/16/24.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <vector>

#include "GameObject.hpp"
#include "Position.hpp"

class Tile;
class Grid;

class Rectangle : public GameObject {
public:
    double top;
    double bottom;
    double left;
    double right;
    std::vector<Position> corner_points;

    Rectangle(double x, double y);

    void initialize(Position, int) override;
    static bool isCollision(const Rectangle&, const Rectangle&);
    [[nodiscard]] bool checkGridCollision(const Grid&) const override;

    [[nodiscard]] double getTop() const;
    [[nodiscard]] double getBottom() const;
    [[nodiscard]] double getLeft() const;
    [[nodiscard]] double getRight() const;
    [[nodiscard]] const std::vector<Position>& getCornerPoints() const;
};

#endif //RECTANGLE_HPP
