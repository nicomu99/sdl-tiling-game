//
// Created by nico on 11/9/24.
//

#ifndef VIEW_HPP
#define VIEW_HPP
#include <SDL_render.h>

#include "Model.hpp"
#include "SDLManager.hpp"

struct Button;

class View {
    SDL_Renderer* renderer;
    SDL_Texture* grass_texture;
    SDL_Texture* wall_texture;
    TTF_Font* font;

    Button& start_button;
    Button& leave_button;

public:
    View(const SDLManager&, Button& start_button, Button& leave_button);

    void renderProjectiles(const Weapon&) const;

    void render(const Model&) const;
    void renderCircle(const Circle& circle) const;
    void renderLivingCircle(const Circle& circle) const;
    void renderTileMap(const Grid &grid) const;
    void renderText(const char* render_text, int text_x, int text_y, SDL_Color render_color, bool center) const;
    void renderScore(int score, const std::string& score_text, int text_y) const;

    void renderHealthBar(int center_x, int center_y, double remaining_health, double initial_health) const;

    void renderPlayer(const Player &player) const;
    void renderButton(Button& button) const;
    void renderPauseScreen(int score) const;
};

#endif //VIEW_HPP
