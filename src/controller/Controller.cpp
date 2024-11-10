//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"
#include "SDLManager.hpp"
#include "Model.hpp"
#include <unordered_map>

#include "Constants.hpp"

// Create the map outside the switch (it could be a static member if reused often)
std::unordered_map<SDL_Keycode, Player::Direction> keyDirectionMap = {
    {SDLK_w, Player::Direction::UP},
    {SDLK_a, Player::Direction::LEFT},
    {SDLK_s, Player::Direction::DOWN},
    {SDLK_d, Player::Direction::RIGHT}
};

Controller::Controller(Model &model, SDLManager &sdl_manager, bool &running): model(model), view(sdl_manager),
                                                                              running(running) {
}

void Controller::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } /*else if (event.type == SDL_KEYDOWN) {
            auto it = keyDirectionMap.find(event.key.keysym.sym);
            if (it != keyDirectionMap.end()) {
                model.movePlayer(it->second);
            }
        }*/
    }

    // Get the current state of the keyboard
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W]) {
        model.movePlayer(Player::Direction::UP);
    }
    if (keystates[SDL_SCANCODE_S]) {
        model.movePlayer(Player::Direction::DOWN);
    }
    if (keystates[SDL_SCANCODE_A]) {
        model.movePlayer(Player::Direction::LEFT);
    }
    if (keystates[SDL_SCANCODE_D]) {
        model.movePlayer(Player::Direction::RIGHT);
    }
}

void Controller::updateModel() {
    model.finishMovingPlayer();
}

void Controller::renderScreen() {
    view.render(model);
}
