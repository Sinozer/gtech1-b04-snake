#pragma once

#include "MainSDLWindow.hpp"
#include "entity/snake/snake.hpp"
#include "entity/fruit/apple.hpp"

class Game
{
public:
    Game(MainSDLWindow *window, unsigned int snakeLen, char snakeDir);
    SDL_bool play();
    int checkCollide();
    void printGame();

private:
    Snake *snake;
    Apple *apple;
    MainSDLWindow *window;
};