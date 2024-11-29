//
// Created by nico on 11/18/24.
//

#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP
#include <vector>

#include "Circle.hpp"
#include "Rectangle.hpp"

class Grid;
class Projectile;
class Zombie;
class Player;

class CollisionManager {
    std::vector<Projectile>& projectiles;
    std::vector<Zombie>& zombies;
    Grid& grid;
    Player& player;
public:
    CollisionManager(std::vector<Projectile>& projectiles, std::vector<Zombie>& zombies, Grid& grid, Player& player);

    static bool isProjectileCircleCollision(Circle& circle, Projectile& projectile);
    static bool isRectangleCircleCollision(Rectangle& rectangle, const Circle& circle, Position& opposite_position);
    bool checkPlayerWallCollision() const;

    void checkProjectileCollisions() const;
    void checkPlayerCollisions() const;
};

#endif //COLLISIONMANAGER_HPP
