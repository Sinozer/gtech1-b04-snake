#pragma once

#include <stdio.h>

#define BODY_SIZE_X 28
#define BODY_SIZE_Y 28

class Body
{
public:
    Body *next;
    Body(int x, int y, char direction);
    int getX();                        // Return the X coordinate (in pixels)
    int getY();                        // Return the Y coordinate (in pixels)
    char getDirection();               // Return the direction
    void setX(int x);                  // Set the X coordinate (in pixels)
    void setY(int y);                  // Set the Y coordinate (in pixels)
    void setDirection(char direction); // Set the direction

private:
    int x; // Position in pixels for this body part on X axis
    int y; // Position in pixels for this body part on Y axis
    char direction; // Direction in char for this body part (North N | South S | West W | East E)
};