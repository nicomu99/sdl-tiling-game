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
        double delta_time = 0.0;
        Uint64 last_frame_start = 0.0;

        while(running) {
            Uint64 frame_start = SDL_GetPerformanceCounter();
            delta_time = static_cast<double>(frame_start - last_frame_start) / static_cast<double>(SDL_GetPerformanceFrequency());
            delta_time = std::min(delta_time, 0.05); // Clamp to a maximum value to prevent huge jumps
            last_frame_start = frame_start;


            controller.handleInput();
            controller.updateModel(delta_time);
            controller.renderScreen();

            /*const Uint64 frame_end = SDL_GetPerformanceCounter();
            double frame_processing_time = static_cast<double>(frame_end - frame_start) / static_cast<double>(SDL_GetPerformanceFrequency()) * 1000.0f;
            // delta_time = std::min(delta_time, Constants::MAX_DELTA_TIME);
            double delay = Constants::FRAME_DELAY - frame_processing_time;
            if(delay > 0) {
                SDL_Delay(static_cast<Uint32>(delay));
            }*/

            double elapsed = static_cast<double>(SDL_GetPerformanceCounter() - frame_start) / static_cast<double>(SDL_GetPerformanceFrequency());
            double frame_rate = 1.0 / elapsed;
            std::cout << "FPS: " << std::to_string(frame_rate) << std::endl;
        }
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
