#pragma once

#include <SDL2/SDL.h>

#define APPLE_SIZE_X 28
#define APPLE_SIZE_Y 28
#define APPLE_BORDER 4

class Apple
{
public:
    Apple();
    int getX();
    int getY();
    void printApple(SDL_Renderer *renderer);
    void debugPrint();
private:
    int x;
    int y;
};