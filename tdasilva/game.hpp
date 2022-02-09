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
    int play(Menu *pause);          // Used while game is on
    int checkCollide();             // Check all collisions
    void printGame(SDL_bool score); // Print the whole game
    void printScore();              // Print the scoreboard

private:
    Snake *snake;          // Instance of the snake introduced in the game
    Apple *apple;          // Instance of the apple introduced in the game
    MainSDLWindow *window; // Instance of the window introduced in the game

    SDL_bool score; // Used to know when to print the scoreboard
    int appleEaten; // Count for apple eaten
};