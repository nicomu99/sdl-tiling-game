//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "Player.hpp"
#include "Grid.hpp"
#include "Zombie.hpp"

class Model {
    Grid grid;
    Player player;
    Zombie zombie;
    double delta_time;

public:
    Model();

    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const Zombie& getZombie() const;

    void movePlayer(Position position);
    void rotatePlayer(Player::Rotation rotation);
    void fireWeapon();
    void checkBulletCollisions();
    void updatePlayer();

    void setDeltaTime(double delta_time);

};

#endif //MODEL_HPP
