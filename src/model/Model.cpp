//
// Created by nico on 11/9/24.
//
#include "Model.hpp"

#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <random>

constexpr Uint32 SPAWN_TIMER = 2000.0;
Uint32 last_spawn = 0;
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution dist(100.0,800.0);

Model::Model(): grid(Grid()), player(Player()), zombies(std::vector<Zombie>()), delta_time(0.0) {
    zombies.emplace_back(400.0, 400.0);
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

void Model::updateMovementState(Position position, Position rotation_target) {
    player.setVelocity(position);
    player.calculateRotationWithTarget(rotation_target);
}

void Model::fireWeapon() {
    player.fireWeapon();
}

void Model::update() {
    player.update(grid, zombies, delta_time);

    for(Zombie& zombie: zombies) {
        zombie.update(grid, player, delta_time);
    }

    size_t erased_objects = std::erase_if(
        zombies,
        [](const Zombie& zombie) {
            return zombie.isDead();
        }
    );
    player.incrementScoreBy(erased_objects);

    // Spawn new zombie
    Uint32 now = SDL_GetTicks();
    if(last_spawn + SPAWN_TIMER < now) {
        double random_x = dist(generator);
        double random_y = dist(generator);
        Position random_pos = Position(random_x, random_y);
        while(Position::computeEuclidean(player.getCenter(), random_pos) < 100) {
            random_x = dist(generator);
            random_y = dist(generator);
            random_pos.setPosition(random_x, random_y);
        }

        zombies.emplace_back(random_x, random_y);
        last_spawn = now;
    }
}

void Model::setDeltaTime(double delta_time) {
    this->delta_time = delta_time;
}
