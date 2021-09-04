#pragma once

#include <iostream>
#include <SDL.h>

enum class direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class input
{
public:
    direction get_direction(SDL_KeyboardEvent* e);
};

