//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Rectangle.hpp"
#include "Weapon.hpp"

class Player : public Rectangle {
    Weapon weapon;
    int score;

public:
    Player();

    [[nodiscard]] const Weapon& getWeapon() const;
    [[nodiscard]] Weapon& getWeapon();
    [[nodiscard]] const int& getScore() const;

    void incrementScoreBy(size_t size);

    void onCollision(Position position) override;
    void afterCollision() override;
    void fireWeapon();
    void update(double delta_time);
};
#endif //PLAYER_HPP
