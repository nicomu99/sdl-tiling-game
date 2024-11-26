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
    int high_score;

public:
    Model(int high_score);

    [[nodiscard]] const int& getHighScore() const;
    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::vector<Zombie>& getZombies() const;

    void updateMovementState(Position position, Position rotation_target);
    void fireWeapon();
    void update(bool& running);

    void setDeltaTime(double delta_time);

};

#endif //MODEL_HPP
