//
// Created by nico on 11/22/24.
//
#include "Zombie.hpp"


#include "Constants.hpp"
#include "Player.hpp"

Zombie::Zombie(): Circle(600, 600, Position(1, 1), Constants::ZOMBIE_SPEED) {
}

Zombie::Zombie(double x, double y): Circle(x, y, Position(1, 1), Constants::ZOMBIE_SPEED) {
}

void Zombie::onCollision(Position opposite_position) {
    move_velocity = opposite_position;
    speed = Constants::RECOIL_SPEED;
    has_been_hit = true;
}

void Zombie::afterCollision() {
    move_velocity = {1, 1};
    speed = Constants::ZOMBIE_SPEED;
    recoil_counter = Constants::RECOIL_COUNT;
    has_been_hit = false;
}

void Zombie::update(const Player& player, double delta_time) {
    calculateRotationWithTarget(player.getCenter());
    move(delta_time);
}
