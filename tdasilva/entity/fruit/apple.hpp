#pragma once

#include <SDL2/SDL.h>

#define APPLE_SIZE_X 28
#define APPLE_SIZE_Y 28
#define APPLE_BORDER 4

class Apple
{
public:
    Apple();                                 // Constructor
    int getX();                              // Return X pos in pixels
    int getY();                              // Return Y pos in pixels
    void setX(int x);                        // Set X pos in pixels
    void setY(int y);                        // Set Y pos in pixels
    void setRandomCoord();                   // Randomize new X and Y
    void printApple(SDL_Renderer *renderer); // Print this apple
    void debugPrint();                       // Print in console (DEBUGGING)

private:
    int x; // Position in pixels for X axis
    int y; // Position in pixels for Y axis
};