//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP
#include <SDL_keycode.h>
#include <bits/unordered_map.h>

#include "Grid.hpp"
#include "Player.hpp"

class Model {
    Grid grid;
    Player player;
public:
    Model();

    Grid& getGrid();
    const Grid& getGrid() const;

    Player &getPlayer();
    const Player &getPlayer() const;

    void movePlayer(Player::Direction direction);

    void finishMovingPlayer();
};

#endif //MODEL_HPP
