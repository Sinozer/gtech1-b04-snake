#include "MainSDLWindow.hpp"
#include "utils/utils.hpp"
#include "utils/text.hpp"

MainSDLWindow::MainSDLWindow(const char *title, int width, int height)
{
    this->window = NULL;
    this->renderer = NULL;
    this->textBox = NULL;
    
    Init(title, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND) != 0)
        Utils::SDL_ExitWithError("SetRenderDrawBlendMode");

    this->textBox = new Text();
    int ret_ttf = textBox->init(this->renderer);
}

MainSDLWindow::~MainSDLWindow()
{
    if (this->renderer != NULL)
        SDL_DestroyRenderer(this->renderer);
    if (this->window != NULL)
        SDL_DestroyWindow(this->window);
    if (this->textBox != NULL)
        delete this->textBox;
}

int MainSDLWindow::Init(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        Utils::SDL_ExitWithError("Init");
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == NULL)
        Utils::SDL_ExitWithError("CreateWindow");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    if (this->renderer == NULL)
        Utils::SDL_ExitWithError("CreateRenderer");
    return 0;
}

void MainSDLWindow::clearRenderer()
{
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0)
        Utils::SDL_ExitWithError("SetRenderDrawColor");
    if (SDL_RenderClear(this->renderer) != 0)
        Utils::SDL_ExitWithError("RenderClear");
}

SDL_Renderer *MainSDLWindow::GetRenderer()
{
    return this->renderer;
}

Text *MainSDLWindow::getTextBox()
{
    return this->textBox;
}