#pragma once

#include <SDL2/SDL_ttf.h>
#include "utils.hpp"

class Text
{
public:
    Text();
    ~Text();

    int init(SDL_Renderer *renderer);
    SDL_Renderer *getRenderer(); // Return the renderer
    TTF_Font *getMenuFont();     // Return the font used for menus
    TTF_Font *getButtonFont();   // Return the font used for buttons
    void printText(const char *text, TTF_Font *font,
                   int x, int y, Uint8 r, Uint8 g, Uint8 b); // Print a text

private:
    SDL_Renderer *renderer; // Renderer used
    TTF_Font *fontMenu;     // Font used in menus
    TTF_Font *fontButton;   // Font used in buttons
};