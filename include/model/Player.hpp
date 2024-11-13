//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <utility>

#include "Grid.hpp"


class Player {
public:
    enum Rotation {
        RIGHT,
        LEFT,
        NONE
    };

    Player();

    const std::pair<float, float> getPosition() const;
    std::pair<float, float> getPosition();
    const std::pair<float, float> getTargetPosition() const;
    std::pair<float, float> getTargetPosition();
    const int getRotationAngle() const;

    void move(Grid);
    void move2(Rotation direction);

    void finishMove();
    void rotatePlayer(Rotation rotation);

    static std::string to_string(Rotation rotation);

private:
    float x_position;
    float y_position;
    float target_x_position;
    float target_y_position;
    int player_rotation;
    bool render;
};
#endif //PLAYER_HPP
