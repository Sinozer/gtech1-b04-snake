#include "game.hpp"
#include "map/map.hpp"
#include "MainSDLWindow.hpp"

Game::Game(MainSDLWindow *window, unsigned int snakeLen, char snakeDir)
{
    this->snake = new Snake(window->GetRenderer() ,snakeLen, snakeDir);
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

SDL_bool Game::play()
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
            case SDL_SCANCODE_D:
                apple->debugPrint();
                continue;

            case SDL_SCANCODE_ESCAPE:
                return SDL_FALSE;

            default:
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
        return SDL_FALSE;
    case 0:
        break;
    case 9:
        return SDL_FALSE;
    default:
        break;
    }
    snake->move();
    printGame(score);
    return SDL_TRUE;
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
    drawNumber(10, 10);
}

char *zero = (char *)"xxxx xx xx xxxx";
char *one = (char *)"  x  x  x  x  x";
char *two = (char *)"xxx  xxxxx  xxx";
char *three = (char *)"xxx  xxxx  xxxx";
char *four = (char *)"x xx xxxx  x  x";
char *five = (char *)"xxxx  xxx  xxxx";
char *six = (char *)"xxxx  xxxx xxxx";
char *seven = (char *)"xxx  x  x  x  x";
char *eight = (char *)"xxxx xxxxx xxxx";
char *nine = (char *)"xxxx xxxx  xxxx";

char **digits[] = {&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine};

void Game::drawDigit(int digit, int posX, int posY)
{
    SDL_Rect rect = {0, 0, 10, 10};
    SDL_SetRenderDrawColor(window->GetRenderer(), 255, 255, 255, 255);

    digit = digit % 10;

    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            if ((*(digits[digit]))[y * 3 + x] == 'x')
            {
                rect.x = posX + x * 10;
                rect.y = posY + y * 10;
                SDL_RenderFillRect(window->GetRenderer(), &rect);
            }
        }
    }
}

void Game::drawNumber(int posX, int posY)
{
    int tempScore = appleEaten;
    int count = 0;

    while (tempScore > 9)
    {
        tempScore /= 10;
        count++;
    }

    int p;

    for (int i = count; i > 0; i--)
    {
        p = pow(10, i);
        tempScore = ((this->appleEaten - this->appleEaten % p) / p) % 10;
        drawDigit(tempScore, posX, posY);
        posX += 40;
    }

    drawDigit(this->appleEaten % 10, posX, posY);
}