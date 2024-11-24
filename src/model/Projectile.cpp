//
// Created by nico on 11/18/24.
//
#include "Projectile.hpp"

constexpr double BULLET_SPEED = 400.0;

Projectile::Projectile(): Circle(0, 0), delta_position(0, 0), has_hit_object(false) {
}

Projectile::Projectile(Position projectile_position, Position delta_position): Circle(projectile_position.x,
                                                                                   projectile_position.y, BULLET_SPEED,
                                                                                   1), delta_position(delta_position),
                                                                               has_hit_object(false) {
}

const bool &Projectile::hasHitObject() const {
    return has_hit_object;
}

void Projectile::setHasHitObject(bool has_hit_wall) {
    this->has_hit_object = has_hit_wall;
}

void Projectile::moveProjectile(double delta_time) {
    performMove(delta_position, delta_time, 1);
}
