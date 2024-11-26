//
// Created by nico on 11/18/24.
//
#include "Weapon.hpp"

#include <SDL_stdinc.h>
#include <SDL_timer.h>

#include "CollisionManager.hpp"

Uint32 last_time = SDL_GetTicks();

Weapon::Weapon(): firing_speed(0.02f), bullet_speed(1.0f), projectiles(std::vector<Projectile>()) {
}

Weapon::Weapon(float firing_speed, float bullet_speed): firing_speed(firing_speed), bullet_speed(bullet_speed),
                                                        projectiles(std::vector<Projectile>()) {
}

const std::vector<Projectile> &Weapon::getProjectiles() const {
    return projectiles;
}

std::vector<Projectile>& Weapon::getProjectiles() {
    return projectiles;
}

void Weapon::fireWeapon(Position firing_position, Position delta_position) {
    if((static_cast<float>(SDL_GetTicks()) - static_cast<float>(last_time)) / 1000.0f < firing_speed) {
        return;
    }
    last_time = SDL_GetTicks();
    projectiles.emplace_back(firing_position, delta_position);
}

void Weapon::updateBullets(double delta_time) {
    for (auto &projectile: projectiles) {
        projectile.moveProjectile(delta_time);
    }
}
