//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

Model::Model(): grid(Grid()), player(Player()), zombies(std::vector<Zombie>()), delta_time(0.0) {
    zombies.emplace_back();
}

const Grid &Model::getGrid() const {
    return grid;
}

const Player &Model::getPlayer() const {
    return player;
}

const std::vector<Zombie> &Model::getZombies() const {
    return zombies;
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

void Model::update() {
    player.update(grid, zombies, delta_time);
    player.rotateGameObject(grid, delta_time);

    for(Zombie& zombie: zombies) {
        zombie.update(grid, player, delta_time);
    }

    std::erase_if(
        zombies,
        [](const Zombie& zombie) {
            return zombie.isDead();
        }
    );
}

void Model::setDeltaTime(double delta_time) {
    this->delta_time = delta_time;
}
