//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Rectangle.hpp"
#include "Weapon.hpp"

class Grid;
class Zombie;

class Player : public Rectangle {
    Weapon weapon;
    int score;

public:
    Player();

    [[nodiscard]] const Weapon& getWeapon() const;
    [[nodiscard]] Weapon& getWeapon();
    [[nodiscard]] const int& getScore() const;

    void update(const Grid &grid, double delta_time);
    void fireWeapon();
    void incrementScoreBy(size_t size);
};
#endif //PLAYER_HPP
