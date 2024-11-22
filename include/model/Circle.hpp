//
// Created by nico on 11/22/24.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "Player.hpp"
#include "Position.hpp"

class Circle : public GameObject{
    int radius;

public:
    Circle();
    Circle(double x, double y);

    [[nodiscard]] bool checkGridCollision(const Grid&) const override;
    void initialize(Position, int) override;

    [[nodiscard]] const int& getRadius() const;
};

#endif //CIRCLE_HPP
