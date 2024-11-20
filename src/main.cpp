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
        float delta_time = 0.0f;

        while(running) {
            const Uint64 frame_start = SDL_GetPerformanceCounter();

            controller.handleInput(delta_time);
            controller.renderScreen();
            controller.updateModel();

            const Uint64 frame_end = SDL_GetPerformanceCounter();

            delta_time = static_cast<float>(frame_end - frame_start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;
            // delta_time = std::min(delta_time, Constants::MAX_DELTA_TIME);

            if(Constants::FRAME_DELAY > delta_time) {
                SDL_Delay(static_cast<Uint32>(floor(Constants::FRAME_DELAY - delta_time)));
            }

            // double elapsed = static_cast<double>(SDL_GetPerformanceCounter() - frame_start) / static_cast<double>(SDL_GetPerformanceFrequency());
            // std::cout << "Current FPS: " << std::to_string(1.0 / elapsed) << std::endl;
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
