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

    void renderCircle() const;

    void renderCircle(const Circle& circle) const;

    void render(const Model&) const;
    void renderTileMap(const Grid &grid) const;
    void renderPlayer(const Player &player) const;
};

#endif //VIEW_HPP
