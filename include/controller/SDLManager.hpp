//
// Created by nico on 11/9/24.
//

#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP
#include <SDL2/SDL.h>
#include <string>

class SDLManager {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* grass_texture = nullptr;
    SDL_Texture* wall_texture = nullptr;

public:
    SDLManager();
    ~SDLManager();

    void loadTexture(SDL_Texture *&texture, const std::string& file_name) const;
    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] SDL_Window *getWindow() const;

    [[nodiscard]] SDL_Texture* getGrassTexture() const;
    SDL_Texture *getWallTexture() const;

    [[nodiscard]] float getCoordinateScaling() const;

    [[nodiscard]] std::pair<int, int> getScreenDimensions() const;
    [[nodiscard]] int getScreenWidth() const;
    [[nodiscard]] int getScreenHeight() const;
    [[nodiscard]] float getDpi() const;
};

#endif //SDLMANAGER_HPP
