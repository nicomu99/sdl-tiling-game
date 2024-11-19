//
// Created by nico on 11/18/24.
//
#include "Projectile.hpp"

#include <iostream>

constexpr float BULLET_SPEED = 10.0f;

Projectile::Projectile(): projectile_position(0, 0), delta_position(0, 0), has_hit_wall(false) { }

Projectile::Projectile(Position projectile_position, Position delta_position): projectile_position(projectile_position), delta_position(delta_position), has_hit_wall(false) { }

const bool & Projectile::hasHitWall() const {
    return has_hit_wall;
}

const Position & Projectile::getPosition() const {
    return projectile_position;
}

void Projectile::setHasHitWall(bool has_hit_wall) {
    this->has_hit_wall = has_hit_wall;
}

void Projectile::moveProjectile() {
    projectile_position += delta_position * BULLET_SPEED;
}
