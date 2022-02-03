#include "utils/utils.hpp"
#include "MainSDLWindow.hpp"
#include "map/map.hpp"
#include "menu/menu.hpp"
#include "game.hpp"

#define FPSLimit 122 // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);

    Menu *pause = new Menu((WINDOW_WIDTH - WINDOW_BORDER) * 0.5, (WINDOW_HEIGHT - WINDOW_BORDER) * 0.75,
                           ((WINDOW_WIDTH - WINDOW_BORDER) / (2 * 2)) + WINDOW_BORDER / 2,
                           (WINDOW_HEIGHT - WINDOW_BORDER) / (4 * 2) + (WINDOW_BORDER / 2), 0, 0, 0, 96);

    pause->addButton(pause->getWidth() * 0.5, pause->getHeight() * 0.25,
                     pause->getX() + (pause->getWidth() / (2 * 2)),
                     pause->getY() + (pause->getHeight() / (4 * 2)), 255, 255, 255, 96);

    pause->addButton(pause->getWidth() * 0.5, pause->getHeight() * 0.25,
                     pause->getX() + (pause->getWidth() / (2 * 2)),
                     pause->getY() + pause->lastButton->getHeight() + pause->lastButton->getHeight() / 2 + (pause->getHeight() / (4 * 2)), 255, 255, 255, 96);

    Game *game = new Game(window, 6, 'E');

    while (game->play(pause))
    {
        unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
        Utils::SDL_Limit_FPS(frame_limit, FPSLimit);
    }
    if (game != NULL)
        delete game;
    if (pause != NULL)
        delete pause;
    if (window != NULL)
        delete window;
    return 0;
}

// TO COMPILE USE: g++ utils/utils.cpp MainSDLWindow.cpp map/map.cpp entity/snake/body.cpp entity/snake/snake.cpp entity/fruit/apple.cpp game.cpp menu/button.cpp menu/menu.cpp main.cpp -lSDL2 -lSDL2_image -o main