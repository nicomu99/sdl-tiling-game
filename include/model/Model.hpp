//
// Created by nico on 11/9/24.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL_video.h>

#include "Grid.hpp"
#include "Player.hpp"
#include "SDLManager.hpp"

class Model {
    Grid grid;
    Player player;
public:
    Model();

    [[nodiscard]] const Grid& getGrid() const;

    [[nodiscard]] const Player& getPlayer() const;

    void movePlayer(float, float);
    void finishMovingPlayer(float);
    void rotatePlayer(Player::Rotation rotation);
};

#endif //MODEL_HPP
