//
// Created by nico on 11/18/24.
//

#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP
#include <vector>

class Grid;
class Projectile;
class Zombie;

class CollisionManager {
public:
    static void checkProjectileCollision(std::vector<Projectile>&, const Grid&, std::vector<Zombie>&);
};

#endif //COLLISIONMANAGER_HPP
