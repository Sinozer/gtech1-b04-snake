#include "text.hpp"

Text::Text()
{
    this->renderer = NULL;
    this->fontMenu = NULL;
    this->fontButton = NULL;
}

int Text::init(SDL_Renderer *renderer_)
{
    this->renderer = renderer_;
    if (TTF_Init() < 0)
    {
        Utils::SDL_ExitWithError("Init TTF\n");
    }
    this->fontMenu = TTF_OpenFont("./ressources/Minecraft.ttf", 60);
    if (this->fontMenu == NULL)
    {
        Utils::SDL_ExitWithError("Init Font\n");
    }
    TTF_SetFontStyle(this->fontMenu, TTF_STYLE_BOLD);
    this->fontButton = TTF_OpenFont("./ressources/Minecraft.ttf", 30);
    if (this->fontButton == NULL)
    {
        Utils::SDL_ExitWithError("Init Font\n");
    }
    return 1;
}

Text::~Text()
{
    TTF_CloseFont(this->fontMenu);
    TTF_CloseFont(this->fontButton);
    TTF_Quit();
}

SDL_Renderer *Text::getRenderer()
{
    return this->renderer;
}

TTF_Font *Text::getMenuFont()
{
    return this->fontMenu;
}

TTF_Font *Text::getButtonFont()
{
    return this->fontButton;
}

void Text::printText(const char *text, TTF_Font *font, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    int tempW = 0;
    int tempH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &tempW, &tempH);
    SDL_Rect dstrect = {x, y, tempW, tempH};
    SDL_RenderCopy(this->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}