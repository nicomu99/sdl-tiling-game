//
// Created by nico on 11/22/24.
//
#include "Zombie.hpp"

#include <iostream>

#include "Player.hpp"

Zombie::Zombie(): Circle(600, 600) { }

Zombie::Zombie(double x, double y): Circle(x, y, Position(1, 1)) { }

void Zombie::update(const Grid& grid, const Player& player, double delta_time) {
    calculateRotationWithTarget(player.getCenter());
    move(grid, delta_time);
}
