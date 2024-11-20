#include <iostream>

#include "Constants.hpp"
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
            // const Uint64 frame_start64 = SDL_GetPerformanceCounter();
            Uint32 frame_start = SDL_GetTicks();

            controller.handleInput();
            controller.renderScreen();
            controller.updateModel();

            //double delta_time = (double)((SDL_GetPerformanceCounter() - frame_start) * 1000) / SDL_GetPerformanceFrequency();
            int frame_time = SDL_GetTicks() - frame_start;

            if(Constants::FRAME_DELAY > frame_time) {
                SDL_Delay(Constants::FRAME_DELAY - frame_time);
                // SDL_Delay((Uint32)(Constants::FRAME_DELAY - delta_time));
            }

            Uint32 msec = SDL_GetTicks() - frame_start;
            std::cout << "Current FPS: " << std::to_string(1000.0 / (double)msec) << std::endl;
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
