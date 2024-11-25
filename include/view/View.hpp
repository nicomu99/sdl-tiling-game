//
// Created by nico on 11/9/24.
//

#ifndef VIEW_HPP
#define VIEW_HPP
#include <SDL_render.h>

#include "Model.hpp"
#include "SDLManager.hpp"

class View {
    SDL_Renderer* renderer;
    SDL_Texture* grass_texture;
    SDL_Texture* wall_texture;
    TTF_Font* font;

public:
    View(const SDLManager&);

    void renderProjectiles(const Weapon&) const;

    void render(const Model&) const;
    void renderCircle(const Circle& circle) const;
    void renderLivingCircle(const Circle& circle) const;
    void renderTileMap(const Grid &grid) const;
    void renderScore(int score) const;

    void renderHealthBar(int center_x, int center_y, double remaining_health, double initial_health) const;

    void renderPlayer(const Player &player) const;
};

#endif //VIEW_HPP
