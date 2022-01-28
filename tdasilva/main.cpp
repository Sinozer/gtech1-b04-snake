#include "utils/utils.hpp"
#include "MainSDLWindow.hpp"
#include "entity/snake/snake.hpp"
#include "map/map.hpp"

#define FPSLimit 122            // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps
#define WINDOW_SQUARE_SIZE_X 32 // Size of the square in pixels for X axis
#define WINDOW_SQUARE_SIZE_Y 32 // Size of the square in pixels for Y axis

#define WINDOW_WIDTH WINDOW_SIZE_X *CHUNK_SIZE_X + WINDOW_BORDER  // Calculate window width
#define WINDOW_HEIGHT WINDOW_SIZE_Y *CHUNK_SIZE_Y + WINDOW_BORDER // Calculate window height

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow();
    window->Init("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Renderer *renderer = window->GetRenderer();
    SDL_bool running = SDL_TRUE;
    unsigned ticks = 0;

    Snake *snake = new Snake(6, 'E');

    while (running)
    {
        unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
        Utils::SDL_Limit_FPS(frame_limit, FPSLimit);

        window->clearRenderer();
        Map::printMap(renderer);
        snake->printSnake(renderer);
        snake->move();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    snake->changeDirection('N');
                    snake->move();
                    continue;

                case SDLK_DOWN:
                    snake->changeDirection('S');
                    snake->move();
                    continue;
                case SDLK_LEFT:
                    snake->changeDirection('W');
                    snake->move();
                    continue;

                case SDLK_RIGHT:
                    snake->changeDirection('E');
                    snake->move();
                    continue;
                case SDLK_b:
                    snake->growTail();
                    continue;
                case SDLK_c:
                    snake->debugPrint();
                    continue;
                case SDLK_ESCAPE:
                    running = SDL_FALSE;
                    break;
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
        SDL_RenderPresent(renderer);
        if (snake->checkCollideWall() ||
            snake->checkCollideBody())
            running = SDL_FALSE;
    }
    if (window != NULL)
        delete (window);
    return 0;
}

// TO COMPILE USE: g++ utils/utils.cpp MainSDLWindow.cpp map/map.cpp entity/snake/body.cpp entity/snake/snake.cpp main.cpp -lSDL2 -o main