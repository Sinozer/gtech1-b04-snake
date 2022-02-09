#pragma once

#include <SDL2/SDL_ttf.h>
#include "utils.hpp"

class Text
{
public:
    Text();
    ~Text();

    int init(SDL_Renderer *renderer);
    SDL_Renderer *getRenderer();
    TTF_Font *getMenuFont();
    TTF_Font *getButtonFont();
    void printText(const char* text, TTF_Font *font, int x, int y, Uint8 r, Uint8 g, Uint8 b);

private:
    SDL_Renderer *renderer;
    TTF_Font *fontMenu;
    TTF_Font *fontButton;
};