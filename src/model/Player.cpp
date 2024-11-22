//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

Player::Player(): Rectangle(150.0, 150.0), weapon(Weapon()) { }

const Weapon & Player::getWeapon() const {
    return weapon;
}

Weapon& Player::getWeapon() {
    return weapon;
}

void Player::fireWeapon() {
    Position delta_position = calculateTrajectory(1);
    weapon.fireWeapon(center, delta_position);
}

void Player::update(const Grid& grid, std::vector<Zombie>& zombie, double delta_time) {
    move(grid, delta_time);
    weapon.updateBullets(grid, zombie);
}
