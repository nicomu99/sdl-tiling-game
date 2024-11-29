//
// Created by nico on 11/22/24.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "GameObject.hpp"

class Circle : public GameObject {
    int radius;

public:
    Circle();
    Circle(double x, double y);
    Circle(double x, double y, double speed, int radius);
    Circle(double x, double y, Position move_velocity, double speed);

    [[nodiscard]] const int& getRadius() const;

    void initialize(Position, int) override;
};

#endif //CIRCLE_HPP
