//
// Created by nico on 11/29/24.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL_pixels.h>
#include <string>
#include <utility>

enum ButtonType {
    START, LEAVE
};

struct Button {
    int x, y;
    int width, height;
    std::string text;
    ButtonType button_type;
    SDL_Color color;

    Button(int x, int y, int width, int height, std::string text, ButtonType button_type)
        : x(x), y(y), width(width), height(height), text(std::move(text)), button_type(button_type), color{255, 0, 0, 255} {
    }

    [[nodiscard]] bool isClicked(int mouse_x, int mouse_y) const {
        return mouse_x > x && mouse_x < x + width && mouse_y > y && mouse_y < y + height;
    }

    void handleMouseDownEvent() {
        color = SDL_Color{0, 255, 0, 255};
    }

    void handleMouseUpEvent() {
        color = SDL_Color{255, 0, 0, 255};
    }
};

#endif //BUTTON_HPP
