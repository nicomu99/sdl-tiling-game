//
// Created by nico on 11/9/24.
//

#ifndef GRID_HPP
#define GRID_HPP
#include <vector>

#include "Tile.hpp"


class Grid {
    std::vector<std::vector<Tile>> tile_map;
public:
    Grid();

    [[nodiscard]] const std::vector<std::vector<Tile>>& getTileMap() const;
    [[nodiscard]] const Tile& getTile(int x_position, int y_position) const;
    [[nodiscard]] const Tile& getTile(Position) const;

    [[nodiscard]] bool isWallAt(Position) const;

    static int toTileCoordinate(double coordinate_position);
};

#endif //GRID_HPP
