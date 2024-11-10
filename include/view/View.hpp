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
    View(SDLManager&);

    void render(const Model& model);

    void renderPlayer(const Player &player);
};

#endif //VIEW_HPP
