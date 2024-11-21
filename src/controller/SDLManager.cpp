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

SDL_Renderer *SDLManager::getRenderer() const {
    return renderer;
}

SDL_Window *SDLManager::getWindow() const {
    return window;
}

float SDLManager::getCoordinateScaling() const {
    return std::min(static_cast<float>(getScreenWidth()) / Constants::VIRTUAL_WIDTH,
                    static_cast<float>(getScreenHeight()) / Constants::VIRTUAL_HEIGHT);
}

float SDLManager::getDpiScaling() const {
    return Constants::REFERENCE_DPI / getDpi();
}

std::pair<int, int> SDLManager::getScreenDimensions() const {
    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);

    return {screen_width, screen_height};
}

int SDLManager::getScreenWidth() const {
    int screen_width;
    SDL_GetWindowSize(window, &screen_width, nullptr);
    return screen_width;
}

int SDLManager::getScreenHeight() const {
    int screen_height;
    SDL_GetWindowSize(window, &screen_height, nullptr);
    return screen_height;
}

float SDLManager::getDpi() const {
    int display_index = SDL_GetWindowDisplayIndex(window);
    if (display_index < 0) {
        SDL_Log("Could not retrieve display number: %s", SDL_GetError());
        display_index = 0;
    }

    float dpi;
    if (SDL_GetDisplayDPI(display_index, &dpi, nullptr, nullptr) != 0) {
        SDL_Log("Could not get DPI for display: %s", SDL_GetError());
        dpi = Constants::REFERENCE_DPI; // Standard dpi value
    }
    return dpi;
}
