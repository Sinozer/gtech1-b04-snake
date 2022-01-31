#include "utils/utils.hpp"
#include "MainSDLWindow.hpp"
#include "map/map.hpp"
#include "game.hpp"

#define FPSLimit 66             // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps
#define WINDOW_SQUARE_SIZE_X 32 // Size of the square in pixels for X axis
#define WINDOW_SQUARE_SIZE_Y 32 // Size of the square in pixels for Y axis

#define WINDOW_WIDTH WINDOW_SIZE_X *CHUNK_SIZE_X + WINDOW_BORDER  // Calculate window width
#define WINDOW_HEIGHT WINDOW_SIZE_Y *CHUNK_SIZE_Y + WINDOW_BORDER // Calculate window height

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow();
    window->Init("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);
    
    SDL_bool running = SDL_TRUE;
    unsigned ticks = 0;

    Game *game = new Game(window, 6, 'E');

    while (running)
    {
        unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
        Utils::SDL_Limit_FPS(frame_limit, FPSLimit);

        running = game->play();
    }
    if (window != NULL)
        delete (window);
    return 0;
}

// TO COMPILE USE: g++ utils/utils.cpp MainSDLWindow.cpp map/map.cpp entity/snake/body.cpp entity/snake/snake.cpp entity/fruit/apple.cpp game.cpp main.cpp -lSDL2 -o main