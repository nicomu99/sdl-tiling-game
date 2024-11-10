//
// Created by nico on 11/9/24.
//
#include "View.hpp"

#include <iostream>

#include "Constants.hpp"

View::View(SDLManager& sdl_manager): renderer(sdl_manager.getRenderer()) { }

void View::render(const Model& model) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const std::vector<std::vector<TileType>>& grid = model.getGrid().getTileMap();
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == TileType::Walkable) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            SDL_Rect render_rect = {Constants::TILE_SIZE * j, Constants::TILE_SIZE * i, Constants::TILE_SIZE, Constants::TILE_SIZE};
            SDL_RenderFillRect(renderer, &render_rect);
        }
    }

    renderPlayer(model.getPlayer());

    SDL_RenderPresent(renderer);
}

void View::renderPlayer(const Player& player) {
    auto [current_x, current_y] = player.getPosition();

    SDL_Rect player_rect = {static_cast<int>(current_x), static_cast<int>(current_y), Constants::TILE_SIZE, Constants::TILE_SIZE};
    SDL_RenderFillRect(renderer, &player_rect);
}
