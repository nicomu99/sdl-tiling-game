//
// Created by nico on 11/18/24.
//
#include "CollisionManager.hpp"

#include <iostream>


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
            projectile.onCollision(Position(0, 0));
        }

        for (Zombie& zombie: this->zombies) {
            if (isProjectileCircleCollision(zombie, projectile)) {
                zombie.onCollision(Position(1, 1));
                projectile.onCollision(Position(0, 0));
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

bool CollisionManager::isRectangleCircleCollision(Rectangle& rectangle, const Circle& circle,
                                                  Position& opposite_position) {
    auto [rect_x, rect_y] = rectangle.getCenter();
    auto [circle_x, circle_y] = circle.getCenter();
    double circle_radius = circle.getRadius();
    double rect_size = Constants::TILE_SIZE;
    double rotation = rectangle.getRotation(); // Ensure rotation is in radians

    // Rotate circle position into rectangle's local coordinate system
    double cos_rotation = cos(-rotation);
    double sin_rotation = sin(-rotation);
    double rotated_circle_x = cos_rotation * (circle_x - rect_x) - sin_rotation * (circle_y - rect_y) + rect_x;
    double rotated_circle_y = sin_rotation * (circle_x - rect_x) + cos_rotation * (circle_y - rect_y) + rect_y;

    // Find the closest point on the rectangle to the circle
    double closest_x = std::max(rect_x - rect_size / 2, std::min(rotated_circle_x, rect_x + rect_size / 2));
    double closest_y = std::max(rect_y - rect_size / 2, std::min(rotated_circle_y, rect_y + rect_size / 2));

    // Check for collision
    double distance_x = rotated_circle_x - closest_x;
    double distance_y = rotated_circle_y - closest_y;
    double distance_squared = distance_x * distance_x + distance_y * distance_y;
    bool collision = distance_squared <= circle_radius * circle_radius;

    if (collision) {
        // Compute the collision normal in rectangle's local coordinates
        double normal_x = distance_x;
        double normal_y = distance_y;
        double length = std::sqrt(normal_x * normal_x + normal_y * normal_y);
        if (length != 0) {
            normal_x /= length;
            normal_y /= length;
        } else {
            // Special case: circle center is on the edge or corner
            normal_x = 0;
            normal_y = 0;
        }

        // Rotate the normal back to world coordinates
        cos_rotation = cos(rotation); // Recalculate for positive rotation
        sin_rotation = sin(rotation);
        double world_normal_x = cos_rotation * normal_x - sin_rotation * normal_y;
        double world_normal_y = sin_rotation * normal_x + cos_rotation * normal_y;

        // Determine the opposite direction
        opposite_position.x = -world_normal_x;
        opposite_position.y = -world_normal_y;
    }

    return collision;
}

bool CollisionManager::checkPlayerWallCollision() const {
    int min_x = static_cast<int>(player.getLeft());
    int max_x = static_cast<int>(player.getRight());
    int min_y = static_cast<int>(player.getTop());
    int max_y = static_cast<int>(player.getBottom());
    for(int i = min_x; i <= max_x; i++) {
        for(int j = min_y; j <= max_y; j++) {
            if(grid.isWallAt(Position(i, j))) {
                return true;
            }
        }
    }
    return false;
}

void CollisionManager::checkPlayerCollisions() const {
    for (Circle& circle: zombies) {
        Position opposite_position{0, 0};
        if (isRectangleCircleCollision(player, circle, opposite_position)) {
            player.onCollision(opposite_position);
            circle.onCollision(-opposite_position);
        }
    }

    if(checkPlayerWallCollision()) {
        player.onCollision(-player.calculateTrajectory());
    }
}
