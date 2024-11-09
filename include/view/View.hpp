//
// Created by nico on 11/9/24.
//

#ifndef VIEW_HPP
#define VIEW_HPP
#include <SDL_render.h>

#include "SDLManager.hpp"

class View {
    SDL_Renderer* renderer;
public:
    View(SDLManager&);
};

#endif //VIEW_HPP
