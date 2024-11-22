//
// Created by nico on 11/9/24.
//
#include "Player.hpp"

#include <SDL_timer.h>

constexpr double SPEED = 300.0;
constexpr int ROTATION_SPEED = 300;
constexpr int MAX_STEPS = 10;
constexpr float STEP_SIZE = 1.0f / MAX_STEPS;
Uint32 last_update = SDL_GetTicks();

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

void Player::update(const Grid& grid, double delta_time) {
    move(grid, delta_time);
    weapon.updateBullets(grid);
}
