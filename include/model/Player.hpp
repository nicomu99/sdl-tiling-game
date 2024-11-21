//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

#include "Grid.hpp"
#include "Rectangle.hpp"
#include "Weapon.hpp"

class Player : public Rectangle {
    Weapon weapon;
    Position move_velocity;
    int rotation_speed;

public:
    enum Rotation {
        RIGHT = 1,
        LEFT = -1,
        NONE = 0
    };

    Player();

    [[nodiscard]] Position getDeltaPosition(double multiplier) const;
    [[nodiscard]] bool checkGridCollision(const Grid &grid) const;
    [[nodiscard]] const Weapon& getWeapon() const;
    [[nodiscard]] Weapon& getWeapon();

    void setVelocity(Position &move_velocity);
    void setRotation(Rotation rotation);

    void move(const Grid&, double);
    void rotatePlayer(const Grid &, double);
    void fireWeapon();

    void checkProjectileCollisions(const Grid & grid);

    void update(const Grid &grid, double delta_time);


    static std::string to_string(Rotation rotation);
};
#endif //PLAYER_HPP
