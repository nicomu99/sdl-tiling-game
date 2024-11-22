//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Rectangle.hpp"
#include "Weapon.hpp"

class Zombie;

class Player : public Rectangle {
    Weapon weapon;

public:
    Player();

    [[nodiscard]] const Weapon& getWeapon() const;
    [[nodiscard]] Weapon& getWeapon();

    void fireWeapon();
    void update(const Grid &grid, std::vector<Zombie>& zombie, double delta_time);
};
#endif //PLAYER_HPP
