//
// Created by nico on 11/18/24.
//
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Position.hpp"

class Projectile {
    Position projectile_position;
    Position delta_position;
    bool has_hit_object;

public:
    Projectile();
    Projectile(Position, Position);

    [[nodiscard]] const bool& hasHitObject() const;
    [[nodiscard]] const Position& getPosition() const;

    void setHasHitObject(bool);

    void moveProjectile(double delta_time);
};

#endif //PROJECTILE_HPP
