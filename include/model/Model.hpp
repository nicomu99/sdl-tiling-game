//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "CollisionManager.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Zombie.hpp"

enum GameState {
    RUNNING, PAUSING, LOST
};

class Model {
    GameState game_state;
    Grid grid;
    Player player;
    std::vector<Zombie> zombies;
    double delta_time;
    int high_score;
    CollisionManager collision_manager;

public:
    Model(int high_score);

    [[nodiscard]] const int& getHighScore() const;
    [[nodiscard]] const Grid& getGrid() const;
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::vector<Zombie>& getZombies() const;
    [[nodiscard]] const GameState& getGameState() const;

    void updateMovementState(Position position, Position rotation_target);
    void fireWeapon();
    void update();

    void setDeltaTime(double delta_time);
    void startGame();
};

#endif //MODEL_HPP
