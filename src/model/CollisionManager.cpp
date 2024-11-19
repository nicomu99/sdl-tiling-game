//
// Created by nico on 11/18/24.
//
#include "CollisionManager.hpp"

void CollisionManager::checkProjectileCollision(std::vector<Projectile>& projectiles, const Grid& grid) {
    for(auto& projectile : projectiles) {
        if(grid.isWallAt(projectile.getPosition())) {
            projectile.setHasHitWall(true);
        }
    }
}
