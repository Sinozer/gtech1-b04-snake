#include "game.hpp"
#include "map/map.hpp"
#include "MainSDLWindow.hpp"

Game::Game(MainSDLWindow *window, unsigned int snakeLen, char snakeDir)
{
    this->snake = new Snake(snakeLen, snakeDir);
    this->apple = new Apple();
    this->window = window;
}

SDL_bool Game::play()
{
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
            case SDLK_d:
            printf("APPLE:\n\tX: %d\n\tY: %d\nHEAD:\n\tX: %d\n\tY: %d\n", apple->getX(), apple->getY(), snake->getHead().getX(), snake->getHead().getY());
                // apple->debugPrint();
                continue;

            case SDLK_ESCAPE:
                return SDL_FALSE;

            default:
                continue;
            }

        case SDL_QUIT:
            return SDL_FALSE;

        default:
            break;
        }
    }
    // printf("%d\n", checkCollide());
    if (checkCollide() < 0)
        return SDL_FALSE;
    // snake->move();
    printGame();
    return SDL_TRUE;
}

int Game::checkCollide()
{
    if (snake->checkCollideWall())
        return -1;
    else if (snake->checkCollideBody())
        return -2;
    else if (snake->getHead().getX() == apple->getX() &&
             snake->getHead().getY() == apple->getY())
    {
        snake->growTail();
        return 1;
    }
    return 0;
}

void Game::printGame()
{
    window->clearRenderer();
    Map::printMap(window->GetRenderer());
    apple->printApple(window->GetRenderer());
    snake->printSnake(window->GetRenderer());
    SDL_RenderPresent(window->GetRenderer());
}