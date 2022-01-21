#include "MainSDLWindow.hpp"
#define FPSLimit 66 // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps
#define WINDOW_WIDTH 576
#define WINDOW_HEIGHT 384
#define GAME_BORDER 2

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR: %s> %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_Limit_FPS(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();
    if (limit < ticks)
        return;
    else if (limit > ticks + FPSLimit)
        SDL_Delay(FPSLimit);
    else
        SDL_Delay(limit - ticks);
}

SDL_Rect Move_Square(SDL_Renderer *renderer, SDL_Rect rect, int x, int y)
{
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) != 0)
        SDL_ExitWithError("SetRenderDrawColor");
    if (SDL_RenderFillRect(renderer, &rect) != 0)
        SDL_ExitWithError("RenderFillRect");
    rect.x += x;
    rect.y += y;
    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0)
        SDL_ExitWithError("SetRenderDrawColor");
    if (SDL_RenderFillRect(renderer, &rect) != 0)
        SDL_ExitWithError("RenderFillRect");
    SDL_RenderPresent(renderer);
    return rect;
}

MainSDLWindow::MainSDLWindow()
{
    this->window = NULL;
    this->renderer = NULL;
}

MainSDLWindow::~MainSDLWindow()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

int MainSDLWindow::Init(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Init");
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == NULL)
        SDL_ExitWithError("CreateWindow");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    if (this->renderer == NULL)
        SDL_ExitWithError("CreateRenderer");
    
    return 0;
}

SDL_Renderer *MainSDLWindow::GetRenderer()
{
    return this->renderer;
}

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow();
    window->Init("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_bool running = SDL_TRUE;
    unsigned ticks = 0;

    if (SDL_SetRenderDrawColor(window->GetRenderer(), 255, 0, 0, 255) != 0)
        SDL_ExitWithError("SetRenderDrawColor");

    SDL_Rect rectangle;
    rectangle.x = 2;
    rectangle.y = 2;
    rectangle.w = 28;
    rectangle.h = 28;

    int snake = SDL_RenderFillRect(window->GetRenderer(), &rectangle);
    if (snake != 0)
        SDL_ExitWithError("RenderFillRect");

    SDL_RenderPresent(window->GetRenderer());

    while (running)
    {
        unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
        SDL_Limit_FPS(frame_limit);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    rectangle = Move_Square(window->GetRenderer(), rectangle, 0, -32);
                    continue;

                case SDLK_DOWN:
                    rectangle = Move_Square(window->GetRenderer(), rectangle, 0, 32);
                    continue;
                case SDLK_LEFT:
                    rectangle = Move_Square(window->GetRenderer(), rectangle, -32, 0);
                    continue;

                case SDLK_RIGHT:
                    rectangle = Move_Square(window->GetRenderer(), rectangle, 32, 0);
                    continue;
                default:
                    continue;
                }

            case SDL_QUIT:
                running = SDL_FALSE;
                break;

            default:
                break;
            }
        }
    }
    if (window != NULL)
        delete (window);
}