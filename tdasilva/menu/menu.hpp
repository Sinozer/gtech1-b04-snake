#pragma once

#include "button.hpp"
#include "../map/map.hpp"
#include "../entity/fruit/apple.hpp"
#include "../entity/snake/snake.hpp"

class Menu
{
public:
    Menu(int width, int height, int x, int y,
         int colorBackgroundR, int colorBackgroundG,
         int colorBackgroundB, int colorBackgroundA);
    ~Menu();

    void init();

    Button *firstButton;
    Button *lastButton;
    Button *selectedButton;

    Button getFirstButton();
    Button getLastButton();
    Button getSelectedButton();

    void setWidth(int width);
    void setHeight(int height);
    int getWidth();
    int getHeight();

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    void setColorBackgroundRGBA(int colorBackgroundR, int colorBackgroundG,
                                int colorBackgroundB, int colorBackgroundA);
    void setColorBackgroundR(int colorBackgroundR);
    void setColorBackgroundG(int colorBackgroundG);
    void setColorBackgroundB(int colorBackgroundB);
    void setColorBackgroundA(int colorBackgroundA);
    int getColorBackgroundR();
    int getColorBackgroundG();
    int getColorBackgroundB();
    int getColorBackgroundA();

    void addButton(int width, int height, int x, int y,
                   int colorBackgroundR, int colorBackgroundG,
                   int colorBackgroundB, int colorBackgroundA);

    int removeButton(int id);

    void changeSelectedButton(char direction);

    int getLen(void);

    void printMenu(MainSDLWindow *window, Apple *apple, Snake *snake);

    SDL_bool active(MainSDLWindow *window, Apple *apple, Snake *snake);

private:
    int width;
    int height;

    int x;
    int y;

    int colorBackgroundR;
    int colorBackgroundG;
    int colorBackgroundB;
    int colorBackgroundA;
};