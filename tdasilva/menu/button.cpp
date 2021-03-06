#include "button.hpp"

Button::Button(int id, const char *title, int width, int height, int x, int y,
               Uint8 colorBackgroundR, Uint8 colorBackgroundG,
               Uint8 colorBackgroundB, Uint8 colorBackgroundA)
{
    this->previous = NULL;
    this->next = NULL;

    this->setId(id);
    this->setTitle(title);

    setWidth(width);
    setHeight(height);

    setX(x);
    setY(y);

    setColorBackgroundRGBA(colorBackgroundR, colorBackgroundG,
                           colorBackgroundB, colorBackgroundA);
}

Button::~Button()
{
}

void Button::setId(int id)
{
    this->id = id;
}

int Button::getId()
{
    return this->id;
}

void Button::setTitle(const char *title)
{
    this->title = title;
}

void Button::setWidth(int width)
{
    this->width = width;
}

void Button::setHeight(int height)
{
    this->height = height;
}

int Button::getWidth()
{
    return this->width;
}

int Button::getHeight()
{
    return this->height;
}

void Button::setX(int x)
{
    this->x = x;
}

void Button::setY(int y)
{
    this->y = y;
}

int Button::getX()
{
    return this->x;
}

int Button::getY()
{
    return this->y;
}

void Button::setColorBackgroundRGBA(Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                                    Uint8 colorBackgroundB, Uint8 colorBackgroundA)
{
    this->colorBackgroundR = colorBackgroundR;
    this->colorBackgroundG = colorBackgroundG;
    this->colorBackgroundB = colorBackgroundB;
    this->colorBackgroundA = colorBackgroundA;
}
void Button::setColorBackgroundR(Uint8 colorBackgroundR)
{
    this->colorBackgroundR = colorBackgroundR;
}

void Button::setColorBackgroundG(Uint8 colorBackgroundG)
{
    this->colorBackgroundG = colorBackgroundG;
}

void Button::setColorBackgroundB(Uint8 colorBackgroundB)
{
    this->colorBackgroundB = colorBackgroundB;
}

void Button::setColorBackgroundA(Uint8 colorBackgroundA)
{
    this->colorBackgroundA = colorBackgroundA;
}

int Button::getColorBackgroundR()
{
    return this->colorBackgroundR;
}

int Button::getColorBackgroundG()
{
    return this->colorBackgroundG;
}

int Button::getColorBackgroundB()
{
    return this->colorBackgroundB;
}

int Button::getColorBackgroundA()
{
    return this->colorBackgroundA;
}

void Button::printButton(MainSDLWindow *window, Button *selectedButton)
{
    SDL_Rect rectangle;

    if (SDL_SetRenderDrawColor(window->GetRenderer(), this->getColorBackgroundR(),
                               this->getColorBackgroundG(), this->getColorBackgroundB(),
                               this->getColorBackgroundA()) != 0)
        Utils::SDL_ExitWithError("SetRenderDrawColor");

    rectangle.x = this->getX();
    rectangle.y = this->getY();
    rectangle.w = this->getWidth();
    rectangle.h = this->getHeight();

    if (SDL_RenderFillRect(window->GetRenderer(), &rectangle) != 0)
        Utils::SDL_ExitWithError("RenderFillRect");

    int tempX;
    int tempY;
    TTF_SizeText(window->getTextBox()->getButtonFont(), this->title, &tempX, &tempY);

    window->getTextBox()->printText(this->title, window->getTextBox()->getButtonFont(),
                                    this->getX() + (this->getWidth() / 2) - (tempX / 2),
                                    this->getY() + (this->getHeight() / 2) - (tempY / 2), 0, 0, 0);

    if (this != selectedButton)
    {
        if (SDL_SetRenderDrawColor(window->GetRenderer(), 0,
                                   0, 0,
                                   96) != 0)
            Utils::SDL_ExitWithError("SetRenderDrawColor");

        rectangle.x = this->getX();
        rectangle.y = this->getY();
        rectangle.w = this->getWidth();
        rectangle.h = this->getHeight();

        if (SDL_RenderFillRect(window->GetRenderer(), &rectangle) != 0)
            Utils::SDL_ExitWithError("RenderFillRect");
    }
}