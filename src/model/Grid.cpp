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

std::vector<std::vector<TileType>>& Grid::getTileMap() {
    return tile_map;
}

const TileType Grid::getTile(int col, int row) const {
    if(col > tile_map[0].size() || row > tile_map.size())
        return TileType::NonWalkable;
    return tile_map[row][col];
}


TileType Grid::getTile(int col, int row) {
    if(col > tile_map[0].size() || row > tile_map.size())
        return TileType::NonWalkable;
    return tile_map[row][col];
}
