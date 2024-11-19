//
// Created by nico on 11/18/24.
//
#include "Weapon.hpp"

#include "CollisionManager.hpp"

Weapon::Weapon(): firing_speed(1.0f), bullet_speed(1.0f), projectiles(std::vector<Projectile>()) {
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
    projectiles.emplace_back(firing_position, delta_position);
}

void Weapon::updateBullets() {
    for (auto &projectile: projectiles) {
        projectile.moveProjectile();
    }

    std::erase_if(
        projectiles,
        [](const Projectile &projectile) {
            return projectile.hasHitWall();
        }
    );
}

void Weapon::checkProjectileCollisions(const Grid &grid) {
    CollisionManager::checkProjectileCollision(projectiles, grid);
}
