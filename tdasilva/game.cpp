#include "game.hpp"
#include "map/map.hpp"
#include "MainSDLWindow.hpp"

Game::Game(MainSDLWindow *window, unsigned int snakeLen, char snakeDir)
{
    this->snake = new Snake(window->GetRenderer(), snakeLen, snakeDir);
    this->apple = new Apple();
    this->window = window;
    this->appleEaten = 0;
    this->score = SDL_FALSE;
}

Game::~Game()
{
    snake->~Snake();
    delete this->snake;
    delete this->apple;
}

int Game::play(Menu *pause)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                snake->changeDirection('N');
                continue;
            case SDL_SCANCODE_DOWN:
                snake->changeDirection('S');
                continue;
            case SDL_SCANCODE_LEFT:
                snake->changeDirection('W');
                continue;
            case SDL_SCANCODE_RIGHT:
                snake->changeDirection('E');
                continue;
            case SDL_SCANCODE_TAB:
                this->score = SDL_TRUE;
                continue;

            case SDL_SCANCODE_B:
                snake->growTail();
                continue;
            case SDL_SCANCODE_C:
                snake->debugPrint();
                continue;

            case SDL_SCANCODE_ESCAPE:
                switch (pause->active(window, apple, snake))
                {
                case 3:
                    break;
                // case 4:
                //     /* code */
                //     break;
                case 4:
                    return -1;
                }
                continue;
            }

        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_TAB:
                this->score = SDL_FALSE;
                continue;

            default:
                continue;
            }

        case SDL_QUIT:
            return SDL_FALSE;

        default:
            break;
        }
    }
    switch (checkCollide())
    {
    case -1:
    case -2:
        return -1;
    case 0:
        break;
    case 9:
        return -1;
    default:
        break;
    }
    snake->move();
    printGame(score);
    return 0;
}

int Game::checkCollide()
{
    Body temp = snake->getHead();

    if (snake->checkCollideWall())
        return -1;
    else if (snake->checkCollideBody())
        return -2;
    else if (snake->getHead().getX() == apple->getX() &&
             snake->getHead().getY() == apple->getY())
    {
        snake->growTail();
        if (snake->getLen() == MAP_SIZE_X * MAP_SIZE_Y)
            return 9;

        do
        {
            apple->setRandomCoord();
            for (int i = 1; i < snake->getLen(); i++)
            {
                temp = *temp.next;
                if (temp.getX() == apple->getX() &&
                    temp.getY() == apple->getY())
                {
                    apple->setRandomCoord();
                    temp = snake->getHead();
                    i = 0;
                    continue;
                }
            }

        } while (snake->getHead().getX() == apple->getX() &&
                 snake->getHead().getY() == apple->getY());
        this->appleEaten++;
        return 1;
    }
    return 0;
}

void Game::printGame(SDL_bool score)
{
    window->clearRenderer();
    Map::printMap(window->GetRenderer());
    apple->printApple(window->GetRenderer());
    snake->printSnake(window->GetRenderer());
    if (score)
        printScore();
    SDL_RenderPresent(window->GetRenderer());
}

void Game::printScore()
{
    SDL_Rect scoreBackground;
    scoreBackground.h = WINDOW_HEIGHT;
    scoreBackground.w = WINDOW_WIDTH;
    scoreBackground.x = 0;
    scoreBackground.y = 0;
    SDL_SetRenderDrawColor(window->GetRenderer(), 0, 0, 0, 96);
    SDL_RenderFillRect(this->window->GetRenderer(), &scoreBackground);
    
    int tempX;
    int tempY;
    std::string tempStr = "SCORE: " + std::to_string(this->appleEaten);
    const char *tempTitle = tempStr.c_str();
    
    TTF_SizeText(window->getTextBox()->getMenuFont(), tempTitle, &tempX, &tempY);

    window->getTextBox()->printText(tempTitle, window->getTextBox()->getMenuFont(),
                                    ((WINDOW_SIZE_X * WINDOW_CHUNK_SIZE_X) * 0.5) - (tempX / 2),
                                    ((WINDOW_SIZE_Y * WINDOW_CHUNK_SIZE_Y) * 0.5) - (tempY / 2), 0, 0, 0);
}