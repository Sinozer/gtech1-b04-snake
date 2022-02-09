#pragma once

#include "button.hpp"
#include "../MainSDLWindow.hpp"
#include "../utils/text.hpp"
#include "../map/map.hpp"
#include "../entity/fruit/apple.hpp"
#include "../entity/snake/snake.hpp"

class Menu
{
public:
    Menu(const char *title, int width, int height, int x, int y,
         int colorBackgroundR, int colorBackgroundG,
         int colorBackgroundB, int colorBackgroundA);
    ~Menu();

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

    void setTitle(const char *title);
    const char *getTitle();

    void setColorBackgroundRGBA(Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                                Uint8 colorBackgroundB, Uint8 colorBackgroundA);
    void setColorBackgroundR(Uint8 colorBackgroundR);
    void setColorBackgroundG(Uint8 colorBackgroundG);
    void setColorBackgroundB(Uint8 colorBackgroundB);
    void setColorBackgroundA(Uint8 colorBackgroundA);
    int getColorBackgroundR();
    int getColorBackgroundG();
    int getColorBackgroundB();
    int getColorBackgroundA();

    void addButton(int id, const char *title, int width, int height, int x, int y,
                   Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                   Uint8 colorBackgroundB, Uint8 colorBackgroundA);

    void addButton(Button *button, int id);

    int removeButton(int id);

    void changeSelectedButton(char direction);

    int getLen(void);

    void printMenu(MainSDLWindow *window, Apple *apple, Snake *snake);

    int activeStart(MainSDLWindow *window);
    int active(MainSDLWindow *window, Apple *apple, Snake *snake);

private:
    int width;
    int height;

    int x;
    int y;

    const char *title;

    Uint8 colorBackgroundR;
    Uint8 colorBackgroundG;
    Uint8 colorBackgroundB;
    Uint8 colorBackgroundA;
};