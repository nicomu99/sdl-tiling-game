//
// Created by nico on 11/9/24.
//

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <string>

namespace Constants {
    constexpr int SCREEN_HEIGHT = 960;
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int TILE_SIZE = 20;
    constexpr int ROW_COUNT = SCREEN_HEIGHT / TILE_SIZE;
    constexpr int COL_COUNT = SCREEN_WIDTH / TILE_SIZE;
    constexpr int VIRTUAL_WIDTH = 800;
    constexpr int VIRTUAL_HEIGHT = 600;
    constexpr float REFERENCE_DPI = 96.0f;
    constexpr double DESIRED_FPS = 60.0;
    constexpr double FRAME_DELAY = 1000.0 / DESIRED_FPS;
    constexpr double MAX_DELTA_TIME = 0.05;
    const std::string SCORE_FILE_NAME = "score.txt";
    constexpr double PLAYER_SPEED = 200.0;
    constexpr double ZOMBIE_SPEED = 130.0;
    constexpr double CIRCLE_SPEED = 200.0;
    constexpr double RECOIL_SPEED = 100.0;
    constexpr int RECOIL_COUNT = 25;
}

#endif //CONSTANTS_HPP
