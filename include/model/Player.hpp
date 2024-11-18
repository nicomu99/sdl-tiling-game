//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

#include "Grid.hpp"
#include "Rectangle.hpp"

class Player : public Rectangle {
public:
    enum Rotation {
        RIGHT = 1,
        LEFT = -1,
        NONE = 0
    };

    Player();

    [[nodiscard]] Point getDeltaPosition(float dpi) const;
    [[nodiscard]] bool checkGridCollision(const Grid &grid) const;

    void move(const Grid&, float, float);
    void rotatePlayer(Rotation rotation, const Grid&);

    static std::string to_string(Rotation rotation);
};
#endif //PLAYER_HPP
