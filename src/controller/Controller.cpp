//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"

#include <iostream>

#include "SDLManager.hpp"
#include "Model.hpp"
#include <unordered_map>

#include "Constants.hpp"

// Create the map outside the switch (it could be a static member if reused often)
std::unordered_map<SDL_Keycode, Player::Rotation> rotation_map = {
    {SDL_SCANCODE_D, Player::Rotation::RIGHT},
    {SDL_SCANCODE_A, Player::Rotation::LEFT}
};

// Custom hash function for diagonal_key_direction_map
struct pair_hash {
    // For any pair containing types T1 and T2 that have a hash function
    template<class T1, class T2>

    // A callable function overload of the operator ()
    // Allows pair_hash to be called like a function
    // Returns an unsigned integer size_t
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        // Hash both elements of the pair
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        // Combine the two hash values
        return h1 ^ (h2 << 1); // Shift h2 to the left by 1 bit and perform XOR
    }
};

std::unordered_map<std::pair<SDL_Scancode, SDL_Scancode>, Player::Rotation, pair_hash> diagonal_key_direction_map = {
    {{SDL_SCANCODE_W, SDL_SCANCODE_A}, Player::Rotation::LEFT},
    {{SDL_SCANCODE_W, SDL_SCANCODE_D}, Player::Rotation::RIGHT},
    {{SDL_SCANCODE_S, SDL_SCANCODE_A}, Player::Rotation::LEFT},
    {{SDL_SCANCODE_S, SDL_SCANCODE_D}, Player::Rotation::RIGHT}
};

Controller::Controller(Model &model, SDLManager &sdl_manager,
                       bool &running): model(model), view(sdl_manager), running(running),
                                       sdl_manager(sdl_manager),
                                       coordinate_scaling(sdl_manager.getCoordinateScaling()),
                                       dpi_scaling(sdl_manager.getDpiScaling()) { }

void Controller::handleDisplayEvent(const SDL_DisplayEvent &display) {
    if (display.event == SDL_WINDOWEVENT_MOVED) {
        auto [width, height] = sdl_manager.getScreenDimensions();
        coordinate_scaling = sdl_manager.getCoordinateScaling();
        dpi_scaling = sdl_manager.getDpiScaling();
    }
}

void Controller::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_WINDOWEVENT) {
            handleDisplayEvent(event.display);
            break;
        }
    }

    // Get the current state of the keyboard
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
    for (const auto &[key_pair, direction]: diagonal_key_direction_map) {
        if (keystates[key_pair.first] && keystates[key_pair.second]) {
            model.movePlayer(coordinate_scaling, dpi_scaling);
            model.rotatePlayer(direction);
            return;
        }
    }

    // Move forward
    for (SDL_Scancode keys[] = {SDL_SCANCODE_W, SDL_SCANCODE_S}; const auto &key: keys) {
        if (keystates[key]) {
            model.movePlayer(coordinate_scaling, dpi_scaling);
        }
    }

    // A rotates the player to the left, D to the right
    for (const auto &[key, direction]: rotation_map) {
        if (keystates[key]) {
            model.rotatePlayer(direction);
            return;
        }
    }

    if(keystates[SDL_SCANCODE_SPACE]) {
        model.fireWeapon();
    }
}

void Controller::renderScreen() const {
    view.render(model, coordinate_scaling);
}

void Controller::updateModel() const {
    model.updatePlayer();
}
