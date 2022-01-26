#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_SIZE_X 18        // Size of the window in square of pixels for X axis
#define WINDOW_SIZE_Y 12        // Size of the window in square of pixels for Y axis
#define WINDOW_BORDER 4         // Size of the window border in pixel (/2 for 1 side)

class MainSDLWindow
{
public:
    MainSDLWindow(void);
    ~MainSDLWindow(void);
    int Init(const char *title, int width, int height);
    void clearRenderer(void);
    SDL_Renderer *GetRenderer(void);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};