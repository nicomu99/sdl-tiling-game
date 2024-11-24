//
// Created by nico on 11/18/24.
//

#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <vector>

#include "Position.hpp"
#include "Projectile.hpp"

class Zombie;
class Grid;

class Weapon {
    float firing_speed;
    float bullet_speed;
    std::vector<Projectile> projectiles;

public:
    Weapon();
    Weapon(float, float);

    [[nodiscard]] const std::vector<Projectile>& getProjectiles() const;
    [[nodiscard]] std::vector<Projectile>& getProjectiles();

    void fireWeapon(Position, Position);
    void updateBullets(const Grid& grid, std::vector<Zombie>& vector, double delta_time);

    void checkProjectileCollisions(const Grid & grid);

};

#endif //WEAPON_HPP
