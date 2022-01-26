#include "utils.hpp"

void Utils::SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR: %s> %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void Utils::SDL_Limit_FPS(unsigned int limit, int FPSLimit)
{
    unsigned int ticks = SDL_GetTicks();
    if (limit < ticks)
        return;
    else if (limit > ticks + FPSLimit)
        SDL_Delay(FPSLimit);
    else
        SDL_Delay(limit - ticks);
}