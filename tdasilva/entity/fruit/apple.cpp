#include <random>
#include <iostream>

#include "apple.hpp"
#include "../../MainSDLWindow.hpp"
#include "../../map/map.hpp"

Apple::Apple()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distX(0, WINDOW_SIZE_X - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distY(0, WINDOW_SIZE_Y - 1);
    this->x = ((WINDOW_BORDER / 2) + (APPLE_BORDER / 2)) + (distX(rng) * CHUNK_SIZE_X);
    this->y = ((WINDOW_BORDER / 2) + (APPLE_BORDER / 2)) + (distY(rng) * CHUNK_SIZE_Y);
}

int Apple::getX()
{
    return this->x;
}

int Apple::getY()
{
    return this->y;
}

void Apple::printApple(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);

    SDL_Rect apple;
    apple.h = APPLE_SIZE_Y;
    apple.w = APPLE_SIZE_X;
    apple.x = this->x;
    apple.y = this->y;

    SDL_RenderFillRect(renderer, &apple);
}

void Apple::debugPrint()
{
    printf("X: %d\nY: %d\n", this->x, this->y);
}