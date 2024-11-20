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
        double delta_time;

        while(running) {
            const Uint64 frame_start = SDL_GetPerformanceCounter();
            // Uint32 frame_start = SDL_GetTicks();

            controller.handleInput(delta_time);
            controller.renderScreen();
            controller.updateModel();

            delta_time = static_cast<double>((SDL_GetPerformanceCounter() - frame_start) * 1000) / static_cast<double>(SDL_GetPerformanceFrequency());
            // int frame_time = SDL_GetTicks() - frame_start;

            if(Constants::FRAME_DELAY > delta_time) {
                // SDL_Delay(Constants::FRAME_DELAY - frame_time);
                SDL_Delay(static_cast<Uint32>(Constants::FRAME_DELAY - delta_time));
            }

            // Uint32 msec = SDL_GetPerformanceCounter() - frame_start;
            // std::cout << "Current FPS: " << std::to_string(1000.0 / (double)msec) << std::endl;
            double elapsed = static_cast<double>(SDL_GetPerformanceCounter() - frame_start) / static_cast<double>(SDL_GetPerformanceFrequency());
            std::cout << "Current FPS: " << std::to_string(1.0 / elapsed) << std::endl;
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
