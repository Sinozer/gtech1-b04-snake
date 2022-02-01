#include <random>
#include <iostream>

#include "apple.hpp"
#include "../../MainSDLWindow.hpp"
#include "../../map/map.hpp"

Apple::Apple()
{
    setRandomCoord();
}

int Apple::getX()
{
    return this->x;
}

int Apple::getY()
{
    return this->y;
}

void Apple::setX(int xPos)
{
    this->x = xPos;
}

void Apple::setY(int yPos)
{
    this->y = yPos;
}

void Apple::setRandomCoord()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distX(0, MAP_SIZE_X - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distY(0, MAP_SIZE_Y - 1);
    this->x = ((MAP_BORDER / 2) + (APPLE_BORDER / 2)) + (distX(rng) * CHUNK_SIZE_X);
    this->y = ((MAP_BORDER / 2) + (APPLE_BORDER / 2)) + (distY(rng) * CHUNK_SIZE_Y);
}

void Apple::printApple(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

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