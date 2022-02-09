#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../utils/utils.hpp"
#include "../MainSDLWindow.hpp"

class Button
{
public:
    Button *previous;
    Button *next;
    Button(int id, const char *title, int width, int height, int x, int y,
           Uint8 colorBackgroundR, Uint8 colorBackgroundG,
           Uint8 colorBackgroundB, Uint8 colorBackgroundA);
    ~Button();

    void setId(int id);
    int getId();

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

    void printButton(MainSDLWindow *window, Button *selectedButton);

private:
    int id;

    int width;
    int height;

    int x;
    int y;

    const char *title;

    int colorBackgroundR;
    int colorBackgroundG;
    int colorBackgroundB;
    int colorBackgroundA;
};