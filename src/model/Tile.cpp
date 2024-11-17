//
// Created by nico on 11/16/24.
//

#include "Tile.hpp"

Tile::Tile(): Rectangle(0, 0), tile_type(TileType::NonWalkable) { }

Tile::Tile(float x, float y, TileType tile_type): Rectangle(x, y), tile_type(tile_type) { }

const TileType &Tile::getTileType() const {
    return tile_type;
}

bool Tile::isNonWalkable() const {
    return tile_type == TileType::NonWalkable;
}

std::string Tile::to_string(TileType tile_type) {
    switch(tile_type) {
        case TileType::Walkable:
            return "Walkable";
        case TileType::NonWalkable:
            return "NonWalkable";
        default:
            return "None";
    }
}
