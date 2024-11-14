//
// Created by nico on 11/9/24.
//

#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP
#include <SDL2/SDL.h>

class SDLManager {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
public:
    SDLManager();
    ~SDLManager();

    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] SDL_Window *getWindow() const;
    [[nodiscard]] float getDisplayDpi() const;
};

#endif //SDLMANAGER_HPP
