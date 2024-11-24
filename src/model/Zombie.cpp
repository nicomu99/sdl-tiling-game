//
// Created by nico on 11/22/24.
//
#include "Zombie.hpp"

#include "Player.hpp"

Zombie::Zombie(): Circle(600, 600) { }

Zombie::Zombie(float x, float y): Circle(x, y) { }

void Zombie::calculateTargetTrajectory(const Player& player) {
    Position relative_position = this->center - player.getCenter();
    double theta = atan2(relative_position.y, relative_position.x);
    double rotation_radians = rotation * M_PI / 180;
    double phi = theta - rotation_radians;

    rotation = static_cast<int>(phi * 180 / M_PI);
    rotation = (rotation + 360) % 360;
}

void Zombie::update(const Grid& grid, const Player& player, double delta_time) {
    calculateTargetTrajectory(player);
    move(grid, delta_time);
}
