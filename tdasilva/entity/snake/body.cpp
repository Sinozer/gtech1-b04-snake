#include "body.hpp"

Body::Body(int x, int y, char direction)
{
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->next = NULL;
}

int Body::getX()
{
    return this->x;
}

int Body::getY()
{
    return this->y;
}

void Body::setX(int x)
{
    this->x = x;
}

void Body::setY(int y)
{
    this->y = y;
}

char Body::getDirection()
{
    return this->direction;
}

void Body::setDirection(char direction)
{
    this->direction = direction;
}