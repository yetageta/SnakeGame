#include "input.h"

direction input::get_direction(SDL_KeyboardEvent* e) {
    SDL_Scancode* scancode = &e->keysym.scancode;

    if (*scancode == SDL_SCANCODE_UP || *scancode == SDL_SCANCODE_W) {
        std::cout << "UP" << "\n";
        return direction::UP;
    }
    else if (*scancode == SDL_SCANCODE_DOWN || *scancode == SDL_SCANCODE_S) {
        std::cout << "DOWN" << "\n";
        return direction::DOWN;
    }
    else if (*scancode == SDL_SCANCODE_LEFT || *scancode == SDL_SCANCODE_A) {
        std::cout << "LEFT" << "\n";
        return direction::LEFT;
    }
    else if (*scancode == SDL_SCANCODE_RIGHT || *scancode == SDL_SCANCODE_D) {
        std::cout << "RIGHT" << "\n";
        return direction::RIGHT;
    }

    return direction::NONE;
}