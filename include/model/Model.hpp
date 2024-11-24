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
    std::vector<Zombie> zombies;
    double delta_time;

public:
    Model();

    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::vector<Zombie>& getZombies() const;

    void updateMovementState(Position position, Position rotation_target);
    void rotatePlayer(Player::Rotation rotation);
    void fireWeapon();
    void checkBulletCollisions();
    void update();

    void setDeltaTime(double delta_time);

};

#endif //MODEL_HPP
