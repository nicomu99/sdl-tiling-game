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

    void render(const Model&, float) const;
    void renderTileMap(const Grid &grid) const;
    void renderPlayer(const Player &player, float) const;
};

#endif //VIEW_HPP
