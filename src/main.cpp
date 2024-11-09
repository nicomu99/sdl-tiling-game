#include <iostream>

#include "Controller.hpp"
#include "Model.hpp"
#include "SDLManager.hpp"

int main() {
    try {
        SDLManager sdl_manager;
        bool running =  true;
        Model model;
        Controller controller(model, sdl_manager, running);

        while(running) {
            controller.handleInput();
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
