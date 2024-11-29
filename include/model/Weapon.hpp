//
// Created by nico on 11/18/24.
//

#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SDL_stdinc.h>
#include <vector>

#include "Position.hpp"
#include "Projectile.hpp"


class Weapon {
    double firing_speed;
    double bullet_speed;
    std::vector<Projectile> projectiles;
    Uint32 last_shot;

public:
    Weapon();
    Weapon(double, double);

    [[nodiscard]] const std::vector<Projectile>& getProjectiles() const;
    [[nodiscard]] std::vector<Projectile>& getProjectiles();

    void fireWeapon(Position, Position);
    void updateBullets(double delta_time);
};

#endif //WEAPON_HPP
