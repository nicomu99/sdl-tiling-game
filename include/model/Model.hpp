//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "Grid.hpp"
#include "Player.hpp"

class Model {
    Grid grid;
    Player player;
public:
    Model();

    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;

    void movePlayer(float, float);
    void rotatePlayer(Player::Rotation rotation);
    void fireWeapon();
    void checkBulletCollisions();
};

#endif //MODEL_HPP
