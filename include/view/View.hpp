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
public:
    View(const SDLManager&);

    void renderProjectiles(const Weapon&) const;

    void renderCircle(const Circle& circle) const;
    void renderLivingCircle(const Circle& circle) const;

    void render(const Model&) const;
    void renderTileMap(const Grid &grid) const;

    void drawHealthBar(int center_x, int center_y, double remaining_health, double initial_health) const;

    void renderPlayer(const Player &player) const;
};

#endif //VIEW_HPP
