//
// Created by nico on 11/18/24.
//
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Circle.hpp"
#include "Position.hpp"

class Projectile : public Circle {
    Position delta_position;
    bool has_hit_object;

public:
    Projectile();
    Projectile(Position, Position);

    [[nodiscard]] const bool& hasHitObject() const;

    void setHasHitObject(bool);

    void moveProjectile(double delta_time);
};

#endif //PROJECTILE_HPP
