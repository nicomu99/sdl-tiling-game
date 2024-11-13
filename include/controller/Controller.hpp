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
public:
    Controller(Model&, SDLManager&, bool&);

    void handleInput() const;
    void updateModel() const;
    void renderScreen();
};

#endif //CONTROLLER_HPP
