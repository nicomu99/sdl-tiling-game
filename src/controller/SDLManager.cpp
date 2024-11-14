//
// Created by nico on 11/9/24.
//
#include "SDLManager.hpp"
#include "Constants.hpp"

#include <stdexcept>

SDLManager::SDLManager() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) + "\n");
    }

    window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
    }
}

SDLManager::~SDLManager() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* SDLManager::getRenderer() const {
    return renderer;
}

SDL_Window* SDLManager::getWindow() const {
    return window;
}

float SDLManager::getDisplayDpi() const {
    float dpi;
    int display_index = SDL_GetWindowDisplayIndex(window);
    if (SDL_GetDisplayDPI(display_index, &dpi, nullptr, nullptr) != 0) {
        printf("SDL_GetDisplayDPI failed: %s\n", SDL_GetError());
        dpi = 96.0f; // Fallback DPI
    }

    return dpi;
}
