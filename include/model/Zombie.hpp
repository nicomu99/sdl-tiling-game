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

    void update(const Grid& grid, const Player& player, double);
};

#endif //ZOMBIE_HPP
