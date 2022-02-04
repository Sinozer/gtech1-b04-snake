#include "text.hpp"

Text::Text(SDL_Renderer *renderer)
{
    TTF_Init();
    this->renderer = renderer;
    this->font = TTF_OpenFont("../ressources/Minecraft.ttf", 25);
}

Text::~Text()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(texture);
}

void Text::printText(char* text, unsigned int r, unsigned int g, unsigned int b)
{
    SDL_Color color = {r, g, b};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
}