//
// Created by nico on 11/9/24.
//
#include "Grid.hpp"
#include "Constants.hpp"

Grid::Grid() {
    std::vector tile_map(Constants::ROW_COUNT, std::vector<TileType>(Constants::COL_COUNT));
    for(int row = 0; row < Constants::ROW_COUNT; row++) {
        for(int col = 0; col < Constants::COL_COUNT; col++) {
            if (row == 0 || col == 0 || row == Constants::ROW_COUNT - 1 || col == Constants::COL_COUNT - 1) {
                tile_map[row][col] = TileType::Walkable;
            } else {
                tile_map[row][col] = TileType::NonWalkable;
            }
        }
    }

    this->tile_map = tile_map;
}

const std::vector<std::vector<TileType>> & Grid::getTileMap() const {
    return tile_map;
}

std::vector<std::vector<TileType>>& Grid::getTileMap() {
    return tile_map;
}
