//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

Model::Model(): grid(Grid()), player(Player()), delta_time(0.0) {
}

const Grid& Model::getGrid() const {
    return grid;
}

const Player& Model::getPlayer() const {
    return player;
}

void Model::movePlayer(Position position) {
    player.setVelocity(position);
}

void Model::rotatePlayer(Player::Rotation rotation) {
    player.setRotation(rotation);
}

void Model::fireWeapon() {
    player.fireWeapon();
}

void Model::updatePlayer() {
    player.update(grid, delta_time);
    player.rotatePlayer(grid, delta_time);
}

void Model::setDeltaTime(double delta_time) {
    this->delta_time = delta_time;
}
