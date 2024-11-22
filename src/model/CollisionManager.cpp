//
// Created by nico on 11/18/24.
//
#include "CollisionManager.hpp"

#include <iostream>

bool isProjectileCircleCollision(Circle& circle, Projectile& projectile) {
    Position circle_center = circle.getCenter();
    Position projectile_center = projectile.getPosition();

    return Position::computeEuclidean(circle_center, projectile_center) <= circle.getRadius();
}

void CollisionManager::checkProjectileCollision(std::vector<Projectile>& projectiles, const Grid& grid, std::vector<Zombie>& zombies) {
    for(auto& projectile : projectiles) {
        if(grid.isWallAt(projectile.getPosition())) {
            projectile.setHasHitObject(true);
        }

        for(Zombie& zombie: zombies) {
            if(isProjectileCircleCollision(zombie, projectile)) {
                zombie.setHasBeenHit(true);
                projectile.setHasHitObject(true);
            }
        }
    }
}
