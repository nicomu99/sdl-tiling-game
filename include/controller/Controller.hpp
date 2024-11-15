//
// Created by nico on 11/9/24.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "Model.hpp"
#include "SDLManager.hpp"
#include "View.hpp"

class Controller {
    Model& model;
    View view;
    bool& running;
    SDLManager& sdl_manager;
    float coordinate_scaling;
    float dpi_scaling;

public:
    Controller(Model&, SDLManager&, bool&);

    void handleDisplayEvent(const SDL_DisplayEvent & display);

    void handleInput();
    void updateModel() const;
    void renderScreen() const;
};

#endif //CONTROLLER_HPP
