#pragma once

#include <stdio.h>
#include "body.hpp"

class Snake
{
public:
    Snake(unsigned int snakeLen, char direction); // Init the snake with the lenght {default: 6} and the direction {default: E} selected
    ~Snake(void);                                 // Destroy all
    Body getHead();
    void printSnake(SDL_Renderer *renderer);      // Display the snake
    void debugPrint(void);
    void move(void);                      // Move the snake | Each refresh
    void changeDirection(char direction); // Change the facing direction of the snake

    void grow(int x, int y, char direction); // When grow fruit is eaten
    void deleteBody(int bodyPos);            // Delete a choosen part of the snake
    int getLen(void);                        // Return the lenght of the snake

private:
    char direction; // North N | South S | West W | East E {default: E}

    Body *head;
};