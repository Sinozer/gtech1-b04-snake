#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../utils/utils.hpp"
#include "../MainSDLWindow.hpp"

class Button
{
public:
    Button *previous; // Get the previous button
    Button *next;     // Get the next button
    Button(int id, const char *title, int width, int height, int x, int y,
           Uint8 colorBackgroundR, Uint8 colorBackgroundG,
           Uint8 colorBackgroundB, Uint8 colorBackgroundA);
    ~Button();

    void setId(int id); // Set the id of the button
    int getId();        // Get the id of the button

    void setWidth(int width);   // Set the width in pixels of the button
    void setHeight(int height); // Set the height in pixels of the button
    int getWidth();             // Get the width in pixels of the button
    int getHeight();            // Get the height in pixels of the button

    void setX(int x); // Set the X pos in pixels of the button
    void setY(int y); // Set the Y pos in pixels of the button
    int getX();       // Get the X pos in pixels of the button
    int getY();       // Get the Y pos in pixels of the button

    void setTitle(const char *title); // Set the title of the button
    const char *getTitle();           // Get the title of the button

    void setColorBackgroundRGBA(Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                                Uint8 colorBackgroundB, Uint8 colorBackgroundA); // All in one fuction to set color
    void setColorBackgroundR(Uint8 colorBackgroundR);                            // Set the red color of the button
    void setColorBackgroundG(Uint8 colorBackgroundG);                            // Set the green color of the button
    void setColorBackgroundB(Uint8 colorBackgroundB);                            // Set the blue color of the button
    void setColorBackgroundA(Uint8 colorBackgroundA);                            // Set the alpha color of the button
    int getColorBackgroundR();                                                   // Get the red color of the button
    int getColorBackgroundG();                                                   // Get the green color of the button
    int getColorBackgroundB();                                                   // Get the blue color of the button
    int getColorBackgroundA();                                                   // Get the alpha color of the button

    void printButton(MainSDLWindow *window, Button *selectedButton); // Print the button

private:
    int id; // Id of the button

    int width;  // Width of the button
    int height; // Height of the button

    int x; // X pos in pixels of the button
    int y; // Y pos in pixels of the button

    const char *title; // Title of the button

    Uint8 colorBackgroundR; // Red color of the button
    Uint8 colorBackgroundG; // Green color of the button
    Uint8 colorBackgroundB; // Blue color of the button
    Uint8 colorBackgroundA; // Alpha color of the button
};