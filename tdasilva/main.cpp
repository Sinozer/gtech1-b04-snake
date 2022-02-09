#include "utils/utils.hpp"
#include "MainSDLWindow.hpp"
#include "map/map.hpp"
#include "menu/menu.hpp"
#include "game.hpp"

#define FPSLimit 122 // 66 = ~15fps | 33 + ~30fps | 16 = ~60fps

int main(void)
{
    MainSDLWindow *window = new MainSDLWindow("Snake", WINDOW_WIDTH, WINDOW_HEIGHT);

    Menu *start = new Menu("SNAKE", (WINDOW_WIDTH - WINDOW_BORDER) * 0.5, (WINDOW_HEIGHT - WINDOW_BORDER) * 0.75,
                           ((WINDOW_WIDTH - WINDOW_BORDER) / (2 * 2)) + WINDOW_BORDER / 2,
                           (WINDOW_HEIGHT - WINDOW_BORDER) / (4 * 2) + (WINDOW_BORDER / 2), 0, 0, 0, 96);

    start->addButton(1, "PLAY", start->getWidth() * 0.5, start->getHeight() * 0.25,
                     start->getX() + (start->getWidth() / (2 * 2)),
                     start->getY() + (start->getHeight() / 4), 255, 255, 255, 255);

    start->addButton(2, "QUIT ;(", start->getWidth() * 0.5, start->getHeight() * 0.25,
                     start->getX() + (start->getWidth() / (2 * 2)),
                     start->lastButton->getY() + start->lastButton->getHeight() + (start->lastButton->getHeight() / 2), 255, 255, 255, 255);

    SDL_bool startBool = SDL_TRUE;

    do
    {
        switch (start->active(window, NULL, NULL))
        {
        case 1:
        {
            Menu *pause = new Menu("PAUSE", (WINDOW_WIDTH - WINDOW_BORDER) * 0.5, (WINDOW_HEIGHT - WINDOW_BORDER) * 0.75,
                                   ((WINDOW_WIDTH - WINDOW_BORDER) / (2 * 2)) + WINDOW_BORDER / 2,
                                   (WINDOW_HEIGHT - WINDOW_BORDER) / (4 * 2) + (WINDOW_BORDER / 2), 0, 0, 0, 96);

            pause->addButton(3, "RESUME", pause->getWidth() * 0.5, pause->getHeight() * 0.25,
                             pause->getX() + (pause->getWidth() / (2 * 2)),
                             start->getY() + (start->getHeight() / 4), 255, 255, 255, 255);

            pause->addButton(4, "GO TO TITLE", pause->getWidth() * 0.5, pause->getHeight() * 0.25,
                             pause->getX() + (pause->getWidth() / (2 * 2)),
                             start->lastButton->getY() + start->lastButton->getHeight() + (start->lastButton->getHeight() / 2), 255, 255, 255, 255);

            Game *game = new Game(window, 6, 'E');

            int gameStatement;

            while (gameStatement = game->play(pause) == 0)
            {
                unsigned int frame_limit = SDL_GetTicks() + FPSLimit;
                Utils::SDL_Limit_FPS(frame_limit, FPSLimit);
            }
            if (game != NULL)
                delete game;
            if (pause != NULL)
                delete pause;
            if (gameStatement == -1)
                startBool = SDL_TRUE;
            break;
        }
        case -1:
            startBool = SDL_FALSE;
            break;
            // default:
            //     continue;
        }
    } while (startBool);

    if (window != NULL)
        delete window;
    return 0;
}

// TO COMPILE USE: g++ utils/utils.cpp utils/text.cpp MainSDLWindow.cpp map/map.cpp entity/snake/body.cpp entity/snake/snake.cpp entity/fruit/apple.cpp game.cpp menu/button.cpp menu/menu.cpp main.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -o main && ./main