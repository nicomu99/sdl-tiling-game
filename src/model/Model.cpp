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

void Model::movePlayer(float coordinate_scaling, float dpi_scaling) {
    player.move(grid, coordinate_scaling, dpi_scaling);
}

void Model::finishMovingPlayer(float coordinate_scaling) {
    player.finishMove(coordinate_scaling);
}

void Model::rotatePlayer(Player::Rotation rotation) {
    player.rotatePlayer(rotation);
}
