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
public:
    static bool isProjectileCircleCollision(Circle& circle, Projectile& projectile);
    static void checkProjectileCollision(std::vector<Projectile>&, const Grid&, std::vector<Zombie>&);
    static bool isRectangleCircleCollision(Rectangle& rectangle, const Circle& circle);
    static void checkRectangleCircleCollision(Rectangle& rectangle, const std::vector<Zombie>& circles);
};

#endif //COLLISIONMANAGER_HPP
