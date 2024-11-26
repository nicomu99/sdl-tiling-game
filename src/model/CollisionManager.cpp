//
// Created by nico on 11/18/24.
//
#include "CollisionManager.hpp"


#include "Circle.hpp"
#include "Constants.hpp"
#include "Projectile.hpp"
#include "Grid.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

CollisionManager::CollisionManager(std::vector<Projectile>& projectiles,
                                   std::vector<Zombie>& zombies, Grid& grid, Player& player)
    : projectiles(projectiles), zombies(zombies), grid(grid), player(player) {
}

bool CollisionManager::isProjectileCircleCollision(Circle& circle, Projectile& projectile) {
    Position circle_center = circle.getCenter();
    Position projectile_center = projectile.getCenter();

    return Position::computeEuclidean(circle_center, projectile_center) <= circle.getRadius();
}

void CollisionManager::checkProjectileCollisions() const {
    for (auto& projectile: this->projectiles) {
        if (grid.isWallAt(projectile.getCenter())) {
            projectile.setHasHitObject(true);
        }

        for (Zombie& zombie: this->zombies) {
            if (isProjectileCircleCollision(zombie, projectile)) {
                zombie.setHasBeenHit(true);
                projectile.setHasHitObject(true);
            }
        }
    }

    // Delete projectiles upon collision
    std::erase_if(
        projectiles,
        [](const Projectile& projectile) {
            return projectile.hasHitObject();
        }
    );

    size_t erased_objects = std::erase_if(
        zombies,
        [](const Zombie& zombie) {
            return zombie.isDead();
        }
    );
    player.incrementScoreBy(erased_objects);
}

bool CollisionManager::isRectangleCircleCollision(Rectangle& rectangle, const Circle& circle) {
    auto [rect_x, rect_y] = rectangle.getCenter();
    auto [circle_x, circle_y] = circle.getCenter();
    double circle_radius = circle.getRadius();
    double rect_size = Constants::TILE_SIZE;
    int rotation = rectangle.getRotation();

    double rotated_circle_x = cos(-rotation) * (circle_x - rect_x) - sin(-rotation) * (circle_y - rect_y) + rect_x;
    double rotated_circle_y = sin(-rotation) * (circle_x - rect_x) + cos(-rotation) * (circle_y - rect_y) + rect_x;

    double closest_x = std::max(rect_x - rect_size / 2, std::min(rotated_circle_x, rect_x + rect_size / 2));
    double closest_y = std::max(rect_y - rect_size / 2, std::min(rotated_circle_y, rect_y + rect_size / 2));

    return pow(closest_x - rotated_circle_x, 2) + pow(closest_y - rotated_circle_y, 2) <= circle_radius;
}

void CollisionManager::checkPlayerCollisions() const {
    for (const Circle& circle: zombies) {
        if (isRectangleCircleCollision(player, circle)) {
            player.setHasBeenHit(true);
        }
    }
}
