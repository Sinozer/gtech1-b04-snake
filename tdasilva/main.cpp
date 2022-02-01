#include "utils/utils.hpp"
#include "MainSDLWindow.hpp"
#include "map/map.hpp"
#include "game.hpp"

#define FPSLimit 122 // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);

    Game *game = new Game(window, 6, 'E');

    while (game->play())
    {
        unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
        Utils::SDL_Limit_FPS(frame_limit, FPSLimit);
    }
    if (game != NULL)
        delete game;
    if (window != NULL)
        delete window;
    return 0;
}

// TO COMPILE USE: g++ utils/utils.cpp MainSDLWindow.cpp map/map.cpp entity/snake/body.cpp entity/snake/snake.cpp entity/fruit/apple.cpp game.cpp main.cpp -lSDL2 -o main