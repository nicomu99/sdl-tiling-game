//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

#include "SDLManager.hpp"

Model::Model(): grid(Grid()), player(Player()) { }

const Grid& Model::getGrid() const {
    return grid;
}

const Player& Model::getPlayer() const {
    return player;
}

void Model::movePlayer(float dpi) {
    player.move(grid, dpi);
}

void Model::finishMovingPlayer(float dpi) {
    player.finishMove(dpi);
}

void Model::rotatePlayer(Player::Rotation rotation) {
    player.rotatePlayer(rotation);
}
