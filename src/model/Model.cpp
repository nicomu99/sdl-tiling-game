//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

Model::Model(): grid(Grid()), player(Player()), delta_time(0.0f) {
}

const Grid& Model::getGrid() const {
    return grid;
}

const Player& Model::getPlayer() const {
    return player;
}

void Model::movePlayer() {
    player.move(grid, delta_time);
}

void Model::rotatePlayer(Player::Rotation rotation) {
    player.rotatePlayer(rotation, grid);
}

void Model::fireWeapon() {
    player.fireWeapon();
}

void Model::updatePlayer() {
    player.update(grid);
}

void Model::setDeltaTime(float delta_time) {
    this->delta_time = delta_time;
}
