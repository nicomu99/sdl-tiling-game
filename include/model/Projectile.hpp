//
// Created by nico on 11/18/24.
//

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Position.hpp"

class Projectile {
    Position projectile_position;
    Position delta_position;
    bool has_hit_wall;
public:
    Projectile();
    Projectile(Position, Position);

    [[nodiscard]] const bool& hasHitWall() const;
    [[nodiscard]] const Position& getPosition() const;

    void setHasHitWall(bool);

    void moveProjectile();
};

#endif //PROJECTILE_HPP
