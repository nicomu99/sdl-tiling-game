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
    double delta_time;
public:
    Model();

    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;

    void movePlayer();
    void rotatePlayer(Player::Rotation rotation);
    void fireWeapon();
    void checkBulletCollisions();
    void updatePlayer();

    void setDeltaTime(double delta_time);
};

#endif //MODEL_HPP
