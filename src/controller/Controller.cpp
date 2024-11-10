//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"
#include "SDLManager.hpp"
#include "Model.hpp"
#include <unordered_map>

// Create the map outside the switch (it could be a static member if reused often)
std::unordered_map<SDL_Keycode, Player::Direction> keyDirectionMap = {
    {SDLK_w, Player::Direction::UP},
    {SDLK_a, Player::Direction::LEFT},
    {SDLK_s, Player::Direction::DOWN},
    {SDLK_d, Player::Direction::RIGHT}
};

Controller::Controller(Model& model, SDLManager& sdl_manager, bool& running): model(model), view(sdl_manager), running(running) { }

void Controller::handleInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
        } else if(event.type == SDL_KEYDOWN) {
            auto it = keyDirectionMap.find(event.key.keysym.sym);
            if (it != keyDirectionMap.end()) {
                model.movePlayer(it->second);
            }
        }
    }
}

void Controller::updateModel() {
    model.finishMovingPlayer();
}

void Controller::renderScreen() {
    view.render(model);
}

