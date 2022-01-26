#pragma once

#include <stdio.h>

#define BODY_SIZE_X 28
#define BODY_SIZE_Y 28

class Body
{
public:
    Body *next;
    Body();
    Body(int x, int y, char direction);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    char getDirection();
    void setDirection(char direction);

private:
    int x;
    int y;
    char direction;
};