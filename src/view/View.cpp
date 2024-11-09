//
// Created by nico on 11/9/24.
//
#include "View.hpp"

#include "Constants.hpp"

View::View(SDLManager& sdl_manager): renderer(sdl_manager.getRenderer()) { }

void View::render(const Model& model) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const std::vector<std::vector<TileType>>& grid = model.getGrid().getTileMap();
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == TileType::Walkable) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

            SDL_Rect renderRect = {Constants::TILE_SIZE * j, Constants::TILE_SIZE * i, Constants::TILE_SIZE, Constants::TILE_SIZE};
            SDL_RenderFillRect(renderer, &renderRect);
        }
    }

    SDL_RenderPresent(renderer);
}
