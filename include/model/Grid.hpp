//
// Created by nico on 11/9/24.
//

#ifndef GRID_HPP
#define GRID_HPP
#include <vector>

enum class TileType {
    Walkable,
    NonWalkable
};

class Grid {
    std::vector<std::vector<TileType>> tile_map;
public:
    Grid();

    const std::vector<std::vector<TileType>>& getTileMap() const;
    std::vector<std::vector<TileType>>& getTileMap();
};

#endif //GRID_HPP
