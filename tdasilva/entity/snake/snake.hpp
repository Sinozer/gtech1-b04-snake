#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "body.hpp"

#define SNAKE_BORDER 4

class Snake
{
public:
    Snake(SDL_Renderer *renderer, unsigned int snakeLen, char direction); // Init the snake with the lenght {default: 6} and the direction {default: E} selected
    ~Snake(void);                                                         // Destroy all
    Body getHead();                                                       // Return the head of the snake
    void printSnake(SDL_Renderer *renderer);                              // Display the snake
    void printTexturedSnake(SDL_Renderer *renderer);                      // Display the snake with textures
    void debugPrint(void);                                                // Print coords & direction of each body parts
    void move(void);                                                      // Move the snake | Each refresh
    void changeDirection(char direction);                                 // Change the facing direction of the snake
    SDL_bool checkCollideWall();                                          // Check if head collide with a wall
    SDL_bool checkCollideBody();                                          // Check if head collide with a body part
    void growTail();                                                      // Increment size of the snake from the tail
    void grow(int x, int y, char direction);                              // Increment size of the snake (usefull for init)
    void growHead();                                                      // Increment size of the snake from the head
    void deleteBody(int bodyPos);                                         // Delete a choosen part of the snake
    int getLen(void);                                                     // Return the lenght of the snake

private:
    char direction; // North N | South S | West W | East E {default: E}

    Body *head;
    SDL_Surface *imageHead;
    SDL_Surface *imageBodyStraight;
    SDL_Surface *imageBodyTurn;
    SDL_Surface *imageTail;
    SDL_Texture *textureHead;
    SDL_Texture *textureBodyStraight;
    SDL_Texture *textureBodyTurn;
    SDL_Texture *textureTail;
};