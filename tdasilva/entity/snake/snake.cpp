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
        return;

    if (snakeLen <= 0)
    {
        grow(CHUNK_SIZE_X, CHUNK_SIZE_Y, direction);
    }
    else
    {
        int x;
        int y;
        for (int i = 0; i < snakeLen; i++)
        {
            switch (direction)
            {
            case 'N':
            case 'S':
                x = CHUNK_SIZE_X;
                y = i * CHUNK_SIZE_Y;
                break;
            case 'W':
            case 'E':
                x = i * CHUNK_SIZE_X;
                y = CHUNK_SIZE_Y;
                break;
            default:
                break;
            }
            grow(x, y, direction);
        }
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

        SDL_RenderPresent(renderer);

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
        printf("X: %d\nY: %d\nDIRECTION: %c\n", temp->getX(), temp->getY(), temp->getDirection());

        temp = temp->next;
    }
}

void Snake::changeDirection(char direction)
{
    switch (direction)
    {
    case 'N':
        if (head->getDirection() != 'S')
            head->setDirection(direction);
        break;
    case 'S':
        if (head->getDirection() != 'N')
            head->setDirection(direction);
        break;
    case 'W':
        if (head->getDirection() != 'E')
            head->setDirection(direction);
        break;
    case 'E':
        if (head->getDirection() != 'W')
            head->setDirection(direction);
        break;
    default:
        break;
    }
}

void Snake::move()
{
    deleteBody(getLen());

    int xPos = head->getX();
    int yPos = head->getY();

    // switch (head->getDirection())
    // {
    // case 'N':
    //     yPos -= CHUNK_SIZE_Y;
    //     break;
    // case 'S':
    //     yPos += CHUNK_SIZE_Y;
    //     break;
    // case 'W':
    //     xPos -= CHUNK_SIZE_X;
    //     break;
    // case 'E':
    //     xPos += CHUNK_SIZE_X;
    //     break;
    // default:
    //     break;
    // }
    grow(xPos, yPos, head->getDirection());
}

void Snake::grow(int x, int y, char direction)
{
    Body *newBody = new Body();
    int xPos = x;
    int yPos = y;

    if (head == NULL)
    {
        Body *newBody = new Body(x, y, 'E');
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

    // Body *temp = head;
    // while (temp != NULL)
    // {
    //     temp->setX(xPos);
    //     temp->setY(yPos);
    //     temp->setDirection(direction);

    //     switch (direction)
    //     {
    //     case 'N':
    //         yPos -= CHUNK_SIZE_Y;
    //         break;
    //     case 'S':
    //         yPos += CHUNK_SIZE_Y;
    //         break;
    //     case 'W':
    //         xPos -= CHUNK_SIZE_X;
    //         break;
    //     case 'E':
    //         xPos += CHUNK_SIZE_X;
    //         break;
    //     default:
    //         break;
    //     }

    //     if (temp->next == NULL)
    //         return;
    //     temp = temp->next;
    // }
    // temp->next = newBody;
    // temp->setX(xPos);
    // temp->setY(yPos);
    // temp->setDirection(direction);
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