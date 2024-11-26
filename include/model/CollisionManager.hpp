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
public:
    CollisionManager(std::vector<Projectile>& projectiles, std::vector<Zombie>& zombies, Grid& grid);

    static bool isProjectileCircleCollision(Circle& circle, Projectile& projectile);
    void checkProjectileCollision() const;
    static bool isRectangleCircleCollision(Rectangle& rectangle, const Circle& circle);
    static void checkRectangleCircleCollision(Rectangle& rectangle, const std::vector<Zombie>& circles);
};

#endif //COLLISIONMANAGER_HPP
