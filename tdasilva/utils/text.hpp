#pragma once

#include <SDL2/SDL_ttf.h>

class Text
{
public:
    Text(SDL_Renderer *renderer);
    ~Text();
    void printText(char* text, unsigned int r, unsigned int g, unsigned int b);
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    TTF_Font *font;
};