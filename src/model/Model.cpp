//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

Model::Model(): grid(Grid()), player(Player()) { }

Grid& Model::getGrid() {
    return grid;
}

const Grid& Model::getGrid() const {
    return grid;
}

Player& Model::getPlayer() {
    return player;
}

const Player& Model::getPlayer() const {
    return player;
}

void Model::movePlayer() {
    player.move(grid);
}

void Model::finishMovingPlayer() {
    player.finishMove();
}

void Model::rotatePlayer(Player::Rotation rotation) {
    player.rotatePlayer(rotation);
}
