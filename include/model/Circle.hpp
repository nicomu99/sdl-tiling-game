//
// Created by nico on 11/22/24.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "GameObject.hpp"
class Grid;

class Circle : public GameObject {
    int radius;

public:
    Circle();
    Circle(double x, double y);

    Circle(double x, double y, Position move_velocity);

    [[nodiscard]] bool checkGridCollision(const Grid&) const override;
    void initialize(Position, int) override;

    [[nodiscard]] const int& getRadius() const;
};

#endif //CIRCLE_HPP
