#include "menu.hpp"

Menu::Menu(const char *title, int width, int height, int x, int y,
           int colorBackgroundR, int colorBackgroundG,
           int colorBackgroundB, int colorBackgroundA)
{
    this->firstButton = NULL;
    this->lastButton = NULL;
    this->selectedButton = NULL;

    setTitle(title);

    setWidth(width);
    setHeight(height);

    setX(x);
    setY(y);

    setColorBackgroundRGBA(colorBackgroundR, colorBackgroundG,
                           colorBackgroundB, colorBackgroundA);
}

Menu::~Menu()
{
}

Button Menu::getFirstButton()
{
    return *firstButton;
}

Button Menu::getLastButton()
{
    return *lastButton;
}

Button Menu::getSelectedButton()
{
    return *selectedButton;
}

void Menu::setWidth(int width)
{
    this->width = width;
}

void Menu::setHeight(int height)
{
    this->height = height;
}

int Menu::getWidth()
{
    return this->width;
}

int Menu::getHeight()
{
    return this->height;
}

void Menu::setX(int x)
{
    this->x = x;
}

void Menu::setY(int y)
{
    this->y = y;
}

int Menu::getX()
{
    return this->x;
}

int Menu::getY()
{
    return this->y;
}

void Menu::setTitle(const char *title)
{
    this->title = title;
}

const char *Menu::getTitle()
{
    return this->title;
}

void Menu::setColorBackgroundRGBA(Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                                  Uint8 colorBackgroundB, Uint8 colorBackgroundA)
{
    this->colorBackgroundR = colorBackgroundR;
    this->colorBackgroundG = colorBackgroundG;
    this->colorBackgroundB = colorBackgroundB;
    this->colorBackgroundA = colorBackgroundA;
}
void Menu::setColorBackgroundR(Uint8 colorBackgroundR)
{
    this->colorBackgroundR = colorBackgroundR;
}

void Menu::setColorBackgroundG(Uint8 colorBackgroundG)
{
    this->colorBackgroundG = colorBackgroundG;
}

void Menu::setColorBackgroundB(Uint8 colorBackgroundB)
{
    this->colorBackgroundB = colorBackgroundB;
}

void Menu::setColorBackgroundA(Uint8 colorBackgroundA)
{
    this->colorBackgroundA = colorBackgroundA;
}

int Menu::getColorBackgroundR()
{
    return this->colorBackgroundR;
}

int Menu::getColorBackgroundG()
{
    return this->colorBackgroundG;
}

int Menu::getColorBackgroundB()
{
    return this->colorBackgroundB;
}

int Menu::getColorBackgroundA()
{
    return this->colorBackgroundA;
}

void Menu::addButton(int id, const char *title, int width, int height, int x, int y,
                     Uint8 colorBackgroundR, Uint8 colorBackgroundG,
                     Uint8 colorBackgroundB, Uint8 colorBackgroundA)
{
    Button *button = new Button(1, title, width, height, x, y,
                                colorBackgroundR, colorBackgroundG,
                                colorBackgroundB, colorBackgroundA);

    if (firstButton == NULL)
    {
        button->setId(id);
        firstButton = button;
        lastButton = button;
        return;
    }
    button->next = this->firstButton;
    firstButton->previous = button;

    Button *temp = this->firstButton;

    do
    {
        if (temp->next != NULL)
            temp = temp->next;
    } while (temp->next != NULL);

    button->setId(id);

    this->lastButton, temp->next = button;
    button->previous = temp;
}

void Menu::addButton(Button *button, int id)
{
    if (firstButton == NULL)
        firstButton = button;
    lastButton = button;

    lastButton->next = button;
}

int Menu::removeButton(int id)
{
    if (getLen() < id)
    {
        return -1;
    }

    Button *temp1 = firstButton;
    Button *temp2, *temp3 = NULL;

    if (id == 1)
    {
        firstButton, lastButton->next = firstButton->next;
        firstButton->previous = lastButton;
        delete temp1;
        return 0;
    }

    while (id-- > 1)
    {
        temp2 = temp1;
        temp1 = temp1->next;
        temp1->previous = temp2;
    }
    temp3 = temp1->next;
    temp2->next = temp3;
    temp3->previous = temp2->next;
    delete temp1;
    return 0;
}

void Menu::changeSelectedButton(char direction)
{
    if (selectedButton != NULL)
    {
        switch (direction)
        {
        case 'U':
            selectedButton = selectedButton->previous;
            break;
        case 'D':
            selectedButton = selectedButton->next;
            break;
        default:
            return;
        }
    }
}

int Menu::getLen(void)
{
    Button *temp = firstButton;
    int buttonLen = 0;

    if (temp == NULL)
    {
        return 0;
    }

    while (temp != NULL)
    {
        buttonLen++;
        temp = temp->next;
    }

    return buttonLen;
}

void Menu::printMenu(MainSDLWindow *window, Apple *apple, Snake *snake)
{
    window->clearRenderer();

    Map::printMap(window->GetRenderer());

    if (apple != NULL)
        apple->printApple(window->GetRenderer());
    if (snake != NULL)
        snake->printSnake(window->GetRenderer());

    SDL_Rect rectangle;

    if (SDL_SetRenderDrawColor(window->GetRenderer(), getColorBackgroundR(),
                               getColorBackgroundG(), getColorBackgroundB(),
                               getColorBackgroundA()) != 0)
        Utils::SDL_ExitWithError("SetRenderDrawColor");

    rectangle.x = getX();
    rectangle.y = getY();
    rectangle.w = getWidth();
    rectangle.h = getHeight();

    if (SDL_RenderFillRect(window->GetRenderer(), &rectangle) != 0)
        Utils::SDL_ExitWithError("RenderFillRect");

    int tempX;
    int tempY;
    TTF_SizeText(window->getTextBox()->getMenuFont(), this->title, &tempX, &tempY);

    window->getTextBox()->printText(this->title, window->getTextBox()->getMenuFont(),
                                    this->getX() + (this->getWidth() / 2) - (tempX / 2),
                                    this->getY() + (this->getHeight() / 35), 0, 0, 0);

    if (this->firstButton != NULL)
    {
        Button *temp = this->firstButton;
        do
        {
            temp->printButton(window, selectedButton);

            temp = temp->next;
        } while (temp != NULL && temp != this->firstButton);
    }
    SDL_RenderPresent(window->GetRenderer());
}

int Menu::activeStart(MainSDLWindow *window)
{
    if (firstButton != NULL)
        selectedButton = firstButton;

    SDL_bool isActive = SDL_TRUE;
    while (isActive)
    {
        unsigned int frame_limit = SDL_GetTicks() + 122;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    changeSelectedButton('U');
                    continue;
                case SDL_SCANCODE_DOWN:
                    changeSelectedButton('D');
                    continue;
                case SDL_SCANCODE_RIGHT:
                    if (selectedButton != NULL)
                        printf("X: %d\nY: %d\nW: %d\nH: %d\nID: %d\n\n", selectedButton->getX(), selectedButton->getY(), selectedButton->getWidth(), selectedButton->getHeight(), selectedButton->getId());
                    continue;
                case SDL_SCANCODE_RETURN:
                    switch (selectedButton->getId())
                    {
                    case 1:
                        return 1;
                        break;
                    case 2:
                        return -1;
                    default:
                        break;
                    }
                case SDL_SCANCODE_ESCAPE:
                    isActive = SDL_FALSE;
                    continue;

                default:
                    return 0;
                }

            case SDL_QUIT:
                return -1;

            default:
                continue;
            }
        }
        printMenu(window, NULL, NULL);
        Utils::SDL_Limit_FPS(frame_limit, 122);
    }
    return 0;
}

int Menu::active(MainSDLWindow *window, Apple *apple, Snake *snake)
{
    if (firstButton != NULL)
        selectedButton = firstButton;

    SDL_bool isActive = SDL_TRUE;
    while (isActive)
    {
        unsigned int frame_limit = SDL_GetTicks() + 122;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                    changeSelectedButton('U');
                    continue;
                case SDL_SCANCODE_DOWN:
                    changeSelectedButton('D');
                    continue;
                case SDL_SCANCODE_RIGHT:
                    if (selectedButton != NULL)
                        printf("X: %d\nY: %d\nW: %d\nH: %d\nID: %d\n\n", selectedButton->getX(), selectedButton->getY(), selectedButton->getWidth(), selectedButton->getHeight(), selectedButton->getId());
                    continue;
                case SDL_SCANCODE_RETURN:
                    switch (selectedButton->getId())
                    {
                    case 3:
                        return 3;
                        break;
                    case 4:
                        return 4;
                    case 5:
                        return 5;
                    }
                case SDL_SCANCODE_ESCAPE:
                    isActive = SDL_FALSE;
                    continue;

                default:
                    continue;
                }

            case SDL_QUIT:
                return SDL_FALSE;

            default:
                continue;
            }
        }
        printMenu(window, apple, snake);
        Utils::SDL_Limit_FPS(frame_limit, 122);
    }
    return 0;
}