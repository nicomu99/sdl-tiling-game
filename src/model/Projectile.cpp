//
// Created by nico on 11/18/24.
//
#include "Projectile.hpp"

constexpr float BULLET_SPEED = 20.0f;

Projectile::Projectile(): projectile_position(0, 0), delta_position(0, 0), has_hit_object(false) { }

Projectile::Projectile(Position projectile_position, Position delta_position): projectile_position(projectile_position), delta_position(delta_position), has_hit_object(false) { }

const bool & Projectile::hasHitObject() const {
    return has_hit_object;
}

const Position & Projectile::getPosition() const {
    return projectile_position;
}

void Projectile::setHasHitObject(bool has_hit_wall) {
    this->has_hit_object = has_hit_wall;
}

void Projectile::moveProjectile() {
    projectile_position += (BULLET_SPEED * delta_position);
}
