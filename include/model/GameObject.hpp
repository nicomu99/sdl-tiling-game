//
// Created by nico on 11/22/24.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Constants.hpp"
#include "Position.hpp"

class Grid;

class GameObject {
public:
    Position center;
    int rotation;
    Position move_velocity;
    int rotation_speed;
    double health_points;
    bool has_been_hit;
    double maximum_health;
    double speed;
    int recoil_counter = Constants::RECOIL_COUNT;

    GameObject();
    GameObject(double x, double y);
    GameObject(double x, double y, double speed);
    GameObject(double x, double y, Position move_velocity, double speed);
    virtual ~GameObject() = default;


    [[nodiscard]] const Position& getCenter() const;
    [[nodiscard]] const int& getRotation() const;
    [[nodiscard]] const double& getHealthPoints() const;
    [[nodiscard]] double getMaximumHealth() const;
    [[nodiscard]] bool isDead() const;

    void setVelocity(Position& move_velocity);
    virtual void onCollision(Position opposite_position) = 0;
    virtual void afterCollision() = 0;

    [[nodiscard]] Position calculateTrajectory() const;
    void calculateRotationWithTarget(Position target_position);

    Position calculateDeltaPosition();
    void performMove(Position position, double delta_time);
    void move(double delta_time, double multiplier = 1);

    virtual void initialize(Position, int) = 0;
};

#endif //GAMEOBJECT_HPP
