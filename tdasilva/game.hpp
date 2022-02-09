#pragma once

#include <iostream>
#include <sstream>
#include "MainSDLWindow.hpp"
#include "menu/menu.hpp"
#include "entity/snake/snake.hpp"
#include "entity/fruit/apple.hpp"

class Game
{
public:
    Game(MainSDLWindow *window, unsigned int snakeLen, char snakeDir);
    ~Game();
    int play(Menu *pause);
    int checkCollide();
    void printGame(SDL_bool score);
    void printScore();

    void drawDigit(int digit, int posX, int posY);
    void drawNumber(int posX, int posY);

private:
    Snake *snake;
    Apple *apple;
    MainSDLWindow *window;

    SDL_bool score;
    int appleEaten;
};