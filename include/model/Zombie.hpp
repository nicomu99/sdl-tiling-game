//
// Created by nico on 11/22/24.
//

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include "Circle.hpp"

class Player;

class Zombie : public Circle {
public:
    Zombie();
    Zombie(double, double);

    void onCollision(Position opposite_position) override;
    void afterCollision() override;

    void update(const Player& player, double delta_time);
};

#endif //ZOMBIE_HPP
