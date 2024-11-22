//
// Created by nico on 11/9/24.
//
#include "Grid.hpp"

#include "Constants.hpp"
#include "Tile.hpp"

Grid::Grid() {
    constexpr auto cast_tile_size = static_cast<float>(Constants::TILE_SIZE);
    std::vector tile_map(Constants::ROW_COUNT, std::vector<Tile>(Constants::COL_COUNT));
    for(int row = 0; row < Constants::ROW_COUNT; row++) {
        for(int col = 0; col < Constants::COL_COUNT; col++) {
            const auto x = static_cast<float>(col) * cast_tile_size + cast_tile_size / 2.0f;
            const auto y = static_cast<float>(row) * cast_tile_size + cast_tile_size / 2.0f;
            if (row == 0 || col == 0 || row == Constants::ROW_COUNT - 1 || col == Constants::COL_COUNT - 1) {
                tile_map[row][col] = Tile{x, y, TileType::NonWalkable};
            } else {
                tile_map[row][col] = Tile(x, y, TileType::Walkable);
            }
        }
    }

    this->tile_map = tile_map;
}

const std::vector<std::vector<Tile>> & Grid::getTileMap() const {
    return tile_map;
}

const Tile& Grid::getTile(int x, int y) const {
    return tile_map[y][x];
}

const Tile& Grid::getTile(Position position) const {
    int x = toTileCoordinate(position.x);
    int y = toTileCoordinate(position.y);

    return tile_map[y][x];
}

bool Grid::isWallAt(Position position) const {
    return getTile(position).getTileType() == TileType::NonWalkable;
}

int Grid::toTileCoordinate(double coordinate_position) {
    return static_cast<int>(coordinate_position) / Constants::TILE_SIZE;
}
