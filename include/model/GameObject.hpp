//
// Created by nico on 11/22/24.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Position.hpp"

class Grid;

class GameObject {
public:
    enum Rotation {
        RIGHT = 1,
        LEFT = -1,
        NONE = 0
    };

    Position center;
    int rotation;
    Position move_velocity;
    int rotation_speed;
    double health_points;
    bool has_been_hit;
    double maximum_health;
    double speed;


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

    void setVelocity(Position &move_velocity);
    void setRotation(Rotation rotation);
    void setHasBeenHit(bool);

    [[nodiscard]] Position calculateTrajectory() const;
    void calculateRotationWithTarget(Position target_position);

    void performMove(Position position, double i, double multiplier);
    void move(const Grid&, double delta_time);

    [[nodiscard]] virtual bool checkGridCollision(const Grid&) const = 0;
    virtual void initialize(Position, int) = 0;

    static std::string to_string(Rotation rotation);
};

#endif //GAMEOBJECT_HPP
