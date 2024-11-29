//
// Created by nico on 11/9/24.
//
#include "Controller.hpp"

#include <iostream>

#include "Button.hpp"
#include "SDLManager.hpp"
#include "Model.hpp"

Controller::Controller(Model& model, SDLManager& sdl_manager,
                       bool& running)
    : model(model), running(running),
      sdl_manager(sdl_manager), start_button(490, 400, 300, 40, std::string("Start Game"), START),
      leave_button(490, 475, 300, 40, std::string("Leave Game"), LEAVE), view(sdl_manager, start_button, leave_button) {
}

void Controller::handleInput() {
    SDL_Event event;
    int x, y;
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    model.updateMovementState(Position(0, 0), Position(x, y));
    std::vector<std::reference_wrapper<Button>> buttons = {start_button, leave_button};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && model.getGameState() != RUNNING && event.button.button == SDL_BUTTON_LEFT) {
            for (Button& button : buttons) {
                if (button.isClicked(x, y)) {
                    button.handleMouseDownEvent();
                }
            }
        } else if (event.type == SDL_MOUSEBUTTONUP && model.getGameState() != RUNNING && event.button.button == SDL_BUTTON_LEFT) {
            for (Button& button : buttons) {
                if (button.isClicked(x, y)) {
                    button.handleMouseUpEvent();
                    if(button.button_type == LEAVE) {
                        running = false;
                    } else if(button.button_type == START) {
                        model.startGame();
                    }
                }
            }
        }
    }

    if (model.getGameState() == RUNNING) {
        // Get the current state of the keyboard
        for (SDL_Scancode keys[] = {SDL_SCANCODE_W, SDL_SCANCODE_S}; const auto& key: keys) {
            if (keystates[key]) {
                model.updateMovementState(Position(1, 1), Position(x, y));
            }
        }

        if (keystates[SDL_SCANCODE_SPACE] || mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            model.fireWeapon();
        }
    }
}

void Controller::renderScreen() const {
    view.render(model);
}

void Controller::updateModel(double delta_time) const {
    if (model.getGameState() == RUNNING) {
        model.setDeltaTime(delta_time);
        model.update();
    }
}
