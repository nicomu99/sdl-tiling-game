//
// Created by nico on 11/9/24.
//

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace Constants {
    constexpr int SCREEN_HEIGHT = 960;
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int TILE_SIZE = 20;
    constexpr int ROW_COUNT = SCREEN_HEIGHT / TILE_SIZE;
    constexpr int COL_COUNT = SCREEN_WIDTH / TILE_SIZE;
    constexpr int VIRTUAL_WIDTH = 800;
    constexpr int VIRTUAL_HEIGHT = 600;
    constexpr float REFERENCE_DPI = 96.0f;
}

#endif //CONSTANTS_HPP
