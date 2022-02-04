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
    Button(int id, int width, int height, int x, int y,
           int colorBackgroundR, int colorBackgroundG,
           int colorBackgroundB, int colorBackgroundA);
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

    void printButton(MainSDLWindow *window, Button *selectedButton);

private:
    int id;

    int width;
    int height;

    int x;
    int y;

    int colorBackgroundR;
    int colorBackgroundG;
    int colorBackgroundB;
    int colorBackgroundA;
};