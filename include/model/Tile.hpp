//
// Created by nico on 11/16/24.
//

#ifndef TILE_HPP
#define TILE_HPP
#include <string>

#include "Rectangle.hpp"

enum class TileType {
    Walkable,
    NonWalkable
};

class Tile : public Rectangle {
    TileType tile_type;

public:
    Tile();
    Tile(double, double, TileType);

    [[nodiscard]] const TileType& getTileType() const;
    [[nodiscard]] bool isNonWalkable() const;
    static std::string to_string(TileType rotation);
    void onCollision(Position opposite_position) override;
    void afterCollision() override;
};

#endif //TILE_HPP
