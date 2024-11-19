//
// Created by nico on 11/18/24.
//

#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP
#include <vector>

#include "Grid.hpp"
#include "Projectile.hpp"

class CollisionManager {
public:
    static void checkProjectileCollision(std::vector<Projectile>&, const Grid&);
};

#endif //COLLISIONMANAGER_HPP
