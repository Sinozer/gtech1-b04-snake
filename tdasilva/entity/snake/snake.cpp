#include <SDL2/SDL.h>

#include "../../MainSDLWindow.hpp"
#include "snake.hpp"
#include "../../utils/utils.hpp"
#include "../../map/map.hpp"

Snake::Snake(unsigned int snakeLen, char direction)
{
    head = NULL;
    if (direction != 'N' &&
        direction != 'S' &&
        direction != 'W' &&
        direction != 'E')
        direction = START_DIRECTION;

    int x = (CHUNK_SIZE_X * START_X) + (MAP_BORDER / 2) + (SNAKE_BORDER / 2);
    int y = (CHUNK_SIZE_Y * START_Y) + (MAP_BORDER / 2) + (SNAKE_BORDER / 2);

    grow(x, y, direction);

    for (int i = 1; i < snakeLen; i++)
    {
        growTail();
    }

    this->direction = direction;
}

Snake::~Snake()
{
    for (int i = 0; i < getLen(); i++)
    {
        deleteBody(i + 1);
    }
}

Body Snake::getHead()
{
    return *head;
}

void Snake::printSnake(SDL_Renderer *renderer)
{
    Body *temp = head;

    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0)
        Utils::SDL_ExitWithError("SetRenderDrawColor");

    if (head == NULL)
        return;

    while (temp != NULL)
    {
        SDL_Rect rectangle;
        rectangle.x = temp->getX();
        rectangle.y = temp->getY();
        rectangle.w = BODY_SIZE_X;
        rectangle.h = BODY_SIZE_Y;

        if (SDL_RenderFillRect(renderer, &rectangle) != 0)
            Utils::SDL_ExitWithError("RenderFillRect");

        temp = temp->next;
    }
}

void Snake::debugPrint(void)
{
    Body *temp = head;

    if (head == NULL)
        return;

    while (temp != NULL)
    {
        printf("X: %d\nY: %d\nDIRECTION: %c\n", temp->getX() / 32, temp->getY() / 32, temp->getDirection());

        temp = temp->next;
    }
    printf("\n\n");
}

void Snake::changeDirection(char direction)
{
    switch (direction)
    {
    case 'N':
        if (head->next->getDirection() != 'S')
            head->setDirection(direction);
        break;
    case 'S':
        if (head->next->getDirection() != 'N')
            head->setDirection(direction);
        break;
    case 'W':
        if (head->next->getDirection() != 'E')
            head->setDirection(direction);
        break;
    case 'E':
        if (head->next->getDirection() != 'W')
            head->setDirection(direction);
        break;
    default:
        break;
    }
}

SDL_bool Snake::checkCollideWall()
{
    if ((head->getX() + 32) / 32 > MAP_SIZE_X ||
        (head->getY() + 32) / 32 > MAP_SIZE_Y ||
        head->getX() < 0 ||
        head->getY() < 0)
        return SDL_TRUE;
    return SDL_FALSE;
}

SDL_bool Snake::checkCollideBody()
{
    Body *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;

        if (head->getX() / 32 == (temp->getX() / 32) &&
            (head->getY()) / 32 == (temp->getY() / 32))
            return SDL_TRUE;
    }
    return SDL_FALSE;
}

void Snake::move()
{
    deleteBody(getLen());

    int xPos = head->getX();
    int yPos = head->getY();

    growHead();
}

void Snake::growTail()
{
    if (head == NULL)
        return;

    Body *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    int xPos = temp->getX();
    int yPos = temp->getY();

    switch (temp->getDirection())
    {
    case 'N':
        yPos += CHUNK_SIZE_Y;
        break;
    case 'S':
        yPos -= CHUNK_SIZE_Y;
        break;
    case 'W':
        xPos += CHUNK_SIZE_X;
        break;
    case 'E':
        xPos -= CHUNK_SIZE_X;
        break;
    default:
        break;
    }

    Body *newBody = new Body(xPos, yPos, temp->getDirection());

    newBody->setX(xPos);
    newBody->setY(yPos);
    newBody->setDirection(temp->getDirection());
    temp->next = newBody;
}

void Snake::grow(int x, int y, char direction)
{
    Body *newBody = new Body(x, y, direction);
    int xPos = x;
    int yPos = y;

    if (head == NULL)
    {
        head = newBody;
        return;
    }

    switch (direction)
    {
    case 'N':
        yPos -= CHUNK_SIZE_Y;
        break;
    case 'S':
        yPos += CHUNK_SIZE_Y;
        break;
    case 'W':
        xPos -= CHUNK_SIZE_X;
        break;
    case 'E':
        xPos += CHUNK_SIZE_X;
        break;
    default:
        break;
    }

    newBody->setX(xPos);
    newBody->setY(yPos);
    newBody->setDirection(direction);
    newBody->next = head;
    head = newBody;
}

void Snake::growHead()
{
    if (head == NULL)
        return;

    int xPos = head->getX();
    int yPos = head->getY();

    switch (head->getDirection())
    {
    case 'N':
        yPos -= CHUNK_SIZE_Y;
        break;
    case 'S':
        yPos += CHUNK_SIZE_Y;
        break;
    case 'W':
        xPos -= CHUNK_SIZE_X;
        break;
    case 'E':
        xPos += CHUNK_SIZE_X;
        break;
    default:
        break;
    }

    Body *newBody = new Body(xPos, yPos, head->getDirection());

    newBody->setX(xPos);
    newBody->setY(yPos);
    newBody->setDirection(head->getDirection());
    newBody->next = head;
    head = newBody;
}

void Snake::deleteBody(int bodyPos)
{
    Body *temp1 = head, *temp2 = NULL;
    int bodyLen = 0;

    if (head == NULL)
        return;
    while (temp1 != NULL)
    {
        temp1 = temp1->next;
        bodyLen++;
    }
    if (bodyLen < bodyPos)
        return;
    temp1 = head;
    if (bodyPos == 1)
    {
        head = head->next;
        delete temp1;
        return;
    }
    while (bodyPos-- > 1)
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }
    temp2->next = temp1->next;
    delete temp1;
}

int Snake::getLen(void)
{
    Body *temp = head;
    int bodyLen = 0;

    if (temp == NULL)
    {
        return 0;
    }

    while (temp != NULL)
    {
        bodyLen++;
        temp = temp->next;
    }

    return bodyLen;
}