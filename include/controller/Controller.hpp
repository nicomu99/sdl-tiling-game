//
// Created by nico on 11/9/24.
//

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "Button.hpp"
#include "Model.hpp"
#include "SDLManager.hpp"
#include "View.hpp"

class Controller {
    Model& model;
    bool& running;
    SDLManager& sdl_manager;
    Button start_button;
    Button leave_button;

    View view;

public:
    Controller(Model&, SDLManager&, bool&);

    void handleInput();
    void renderScreen() const;

    void updateModel(double delta_time) const;
};

#endif //CONTROLLER_HPP
