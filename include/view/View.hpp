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

    void render(const Model& model) const;
    void renderPlayer(const Player &player) const;
};

#endif //VIEW_HPP
