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
                tile_map[row][col] = TileType::NonWalkable;
            } else {
                tile_map[row][col] = TileType::Walkable;
            }
        }
    }

    this->tile_map = tile_map;
}

const std::vector<std::vector<TileType>> & Grid::getTileMap() const {
    return tile_map;
}

TileType Grid::getTile(int x_position, int y_position) const {
    if(x_position >= tile_map[0].size() || y_position >= tile_map.size())
        return TileType::NonWalkable;
    return tile_map[y_position][x_position];
}
