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

    Button *firstButton;    // First button of the menu
    Button *lastButton;     // Last button of the menu
    Button *selectedButton; // Selected button of the menu

    Button getFirstButton();    // Return the first button of the menu
    Button getLastButton();     // Return the last button of the menu
    Button getSelectedButton(); // Return the focused button

    void setWidth(int width);   // Set the width in pixels of the menu
    void setHeight(int height); // Set the height in pixels of the menu
    int getWidth();             // Get the width in pixels of the menu
    int getHeight();            // Get the height in pixels of the menu

    void setX(int x); // Set the X pos in pixels of the menu
    void setY(int y); // Set the Y pos in pixels of the menu
    int getX();       // Get the X pos in pixels of the menu
    int getY();       // Get the Y pos in pixels of the menu

    void setTitle(const char *title); // Set the title of the menu
    const char *getTitle();           // Return the title of the menu

    void setColorBackgroundRGBA(Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                                Uint8 colorBackgroundB, Uint8 colorBackgroundA); // All in one fuction to set color
    void setColorBackgroundR(Uint8 colorBackgroundR);                            // Set the red color of the menu background
    void setColorBackgroundG(Uint8 colorBackgroundG);                            // Set the green color of the menu background
    void setColorBackgroundB(Uint8 colorBackgroundB);                            // Set the blue color of the menu background
    void setColorBackgroundA(Uint8 colorBackgroundA);                            // Set the alpha color of the menu background
    int getColorBackgroundR();                                                   // Get the red color of the menu background
    int getColorBackgroundG();                                                   // Get the green color of the menu background
    int getColorBackgroundB();                                                   // Get the blue color of the menu background
    int getColorBackgroundA();                                                   // Get the alpha color of the menu background

    void addButton(int id, const char *title, int width, int height, int x, int y,
                   Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                   Uint8 colorBackgroundB, Uint8 colorBackgroundA); // Add a new button

    void addButton(Button *button, int id); // Add a new button

    void changeSelectedButton(char direction); // Change the focused button

    int getLen(void); // Return how much button the menu have

    void printMenu(MainSDLWindow *window, Apple *apple, Snake *snake); // Print the menu

    int active(MainSDLWindow *window, Apple *apple, Snake *snake); // Called when menu in running

private:
    int width;  // Width of the menu
    int height; // Height of the menu

    int x; // X pos in pixels of the menu
    int y; // Y pos in pixels of the menu

    const char *title; // Title of the menu

    Uint8 colorBackgroundR; // Red color of the menu background
    Uint8 colorBackgroundG; // Green color of the menu background
    Uint8 colorBackgroundB; // Blue color of the menu background
    Uint8 colorBackgroundA; // Alpha color of the menu background
};