//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <utility>

#include "Grid.hpp"
#include "Rectangle.hpp"

class Player : public Rectangle {
public:
    enum Rotation {
        RIGHT,
        LEFT,
        NONE
    };

    Player();

    std::pair<float, float> getDeltaPosition(float dpi) const;

    void move(const Grid&, float, float);
    void rotatePlayer(Rotation rotation);

    static std::string to_string(Rotation rotation);
};
#endif //PLAYER_HPP
