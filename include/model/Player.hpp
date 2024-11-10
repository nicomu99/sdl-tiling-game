//
// Created by nico on 11/9/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <utility>

#include "Grid.hpp"


class Player {
public:
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE,
        LEFTUP,
        RIGHTUP,
        LEFTDOWN,
        RIGHTDOWN
    };

    Player();

    Player(int x_position, int y_position);

    const std::pair<float, float> getPosition() const;
    std::pair<float, float> getPosition();
    const std::pair<int, int> getTargetPosition() const;
    std::pair<int, int> getTargetPosition();
    Direction getDirection();
    const Direction getDirection() const;

    void move(Direction, Grid);
    void move2(Direction direction);

    void finishMove();

    static std::pair<int, int> toPair(Direction dir);
private:
    float x_position;
    float y_position;
    int target_x_position;
    int target_y_position;
    bool render;

    Direction move_direction;
};
#endif //PLAYER_HPP
