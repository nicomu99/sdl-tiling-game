//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"

#include "SDLManager.hpp"
#include "Model.hpp"

Controller::Controller(Model &model, SDLManager &sdl_manager,
                       bool &running): model(model), view(sdl_manager), running(running),
                                       sdl_manager(sdl_manager) { }

void Controller::handleInput() const {

    SDL_Event event;
    int x, y;
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    model.updateMovementState(Position(0, 0), Position(x, y));
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    // Get the current state of the keyboard
    for (SDL_Scancode keys[] = {SDL_SCANCODE_W, SDL_SCANCODE_S}; const auto &key: keys) {
        if (keystates[key]) {
            model.updateMovementState(Position(1, 1), Position(x, y));
        }
    }

    if(keystates[SDL_SCANCODE_SPACE] || mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        model.fireWeapon();
    }
}

void Controller::renderScreen() const {
    view.render(model);
}

void Controller::updateModel(double delta_time) const {
    model.setDeltaTime(delta_time);
    model.update();
}
