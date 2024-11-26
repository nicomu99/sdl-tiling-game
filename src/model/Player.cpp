//
// Created by nico on 11/9/24.
//
#include "Player.hpp"
#include "Grid.hpp"

Player::Player(): Rectangle(150.0, 150.0), weapon(Weapon()), score(0) {
}

const Weapon& Player::getWeapon() const {
    return weapon;
}

Weapon& Player::getWeapon() {
    return weapon;
}

const int& Player::getScore() const {
    return score;
}

void Player::update(const Grid& grid, double delta_time) {
    move(grid, delta_time);
    weapon.updateBullets(delta_time);
    initialize(center, rotation);
}

void Player::fireWeapon() {
    Position delta_position = calculateTrajectory();
    weapon.fireWeapon(center, delta_position);
}

void Player::incrementScoreBy(size_t size) {
    score += static_cast<int>(size);
}


