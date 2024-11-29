//
// Created by nico on 11/18/24.
//
#include "Weapon.hpp"

#include <SDL_timer.h>

#include "CollisionManager.hpp"

Weapon::Weapon(): firing_speed(0.02), bullet_speed(1.0), projectiles(std::vector<Projectile>()),
                  last_shot(SDL_GetTicks()) {
}

Weapon::Weapon(double firing_speed, double bullet_speed)
    : firing_speed(firing_speed), bullet_speed(bullet_speed),
      projectiles(std::vector<Projectile>()), last_shot(SDL_GetTicks()) {
}

const std::vector<Projectile>& Weapon::getProjectiles() const {
    return projectiles;
}

std::vector<Projectile>& Weapon::getProjectiles() {
    return projectiles;
}

void Weapon::fireWeapon(Position firing_position, Position delta_position) {
    if ((static_cast<float>(SDL_GetTicks()) - static_cast<float>(last_shot)) / 1000.0f < firing_speed) {
        return;
    }
    last_shot = SDL_GetTicks();
    projectiles.emplace_back(firing_position, delta_position);
}

void Weapon::updateBullets(double delta_time) {
    for (auto& projectile: projectiles) {
        projectile.moveProjectile(delta_time);
    }
}
