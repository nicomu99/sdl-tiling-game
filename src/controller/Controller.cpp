//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"
#include "SDLManager.hpp"
#include "Model.hpp"

Controller::Controller(Model& model, SDLManager& sdl_manager, bool& running): model(model), view(sdl_manager), running(running) { }

void Controller::handleInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
        }
    }
}

