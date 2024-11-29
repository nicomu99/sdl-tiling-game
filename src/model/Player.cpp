//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include "Constants.hpp"

Player::Player(): Rectangle(150.0, 150.0, Constants::PLAYER_SPEED), weapon(Weapon()), score(0) {
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

void Player::incrementScoreBy(size_t size) {
    score += static_cast<int>(size);
}

void Player::onCollision(Position opposite_position) {
    health_points -= 10;
    move_velocity = opposite_position;
    has_been_hit = true;
    speed = Constants::RECOIL_SPEED;
}

void Player::afterCollision() {
    recoil_counter = Constants::RECOIL_COUNT;
    has_been_hit = false;
    speed = Constants::PLAYER_SPEED;
}

void Player::update(double delta_time) {
    move(delta_time);
    initialize(center, rotation);

    weapon.updateBullets(delta_time);
}

void Player::fireWeapon() {
    Position delta_position = calculateTrajectory();
    weapon.fireWeapon(center, delta_position);
}
