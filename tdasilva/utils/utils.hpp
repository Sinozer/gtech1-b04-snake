#pragma once

#include <SDL2/SDL.h>

class Utils
{
public:
    void static SDL_ExitWithError(const char *message); // Try and catch errors, return message if error occurs
    void static SDL_Limit_FPS(unsigned int limit, int FPSLimit); // Limitation FPS function
};