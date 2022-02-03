#include "menu.hpp"

Menu::Menu(int width, int height, int x, int y,
           int colorBackgroundR, int colorBackgroundG,
           int colorBackgroundB, int colorBackgroundA)
{
    init();

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

void Menu::init()
{
    this->firstButton == NULL;
    this->lastButton == NULL;
    this->selectedButton == NULL;
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

void Menu::setColorBackgroundRGBA(int colorBackgroundR, int colorBackgroundG,
                                  int colorBackgroundB, int colorBackgroundA)
{
    this->colorBackgroundR = colorBackgroundR;
    this->colorBackgroundG = colorBackgroundG;
    this->colorBackgroundB = colorBackgroundB;
    this->colorBackgroundA = colorBackgroundA;
}
void Menu::setColorBackgroundR(int colorBackgroundR)
{
    this->colorBackgroundR = colorBackgroundR;
}

void Menu::setColorBackgroundG(int colorBackgroundG)
{
    this->colorBackgroundG = colorBackgroundG;
}

void Menu::setColorBackgroundB(int colorBackgroundB)
{
    this->colorBackgroundB = colorBackgroundB;
}

void Menu::setColorBackgroundA(int colorBackgroundA)
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

void Menu::addButton(int width, int height, int x, int y,
                     int colorBackgroundR, int colorBackgroundG,
                     int colorBackgroundB, int colorBackgroundA)
{
    printf("start\n");
    Button *button = new Button(1, width, height, x, y,
                                colorBackgroundR, colorBackgroundG,
                                colorBackgroundB, colorBackgroundA);

    // this->firstButton = NULL;

    if (firstButton == NULL)
    {
        printf("NULL\n");
        firstButton = button;
        return;
    }
    printf("NOTNULL\n");
    button->next = this->firstButton;
    firstButton->previous = button;

    int newId = 2;
    Button *temp = this->firstButton;

    while (temp->next != NULL)
    {
        newId++;
        temp = temp->next;
    }

    button->setId(newId);

    this->lastButton, temp->next = button;
    button->previous = temp;
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

    if (this->firstButton != NULL)
    {
        Button *temp = this->firstButton;
        do
        {
            if (SDL_SetRenderDrawColor(window->GetRenderer(), temp->getColorBackgroundR(),
                                       temp->getColorBackgroundG(), temp->getColorBackgroundB(),
                                       temp->getColorBackgroundA()) != 0)
                Utils::SDL_ExitWithError("SetRenderDrawColor");

            rectangle.x = temp->getX();
            rectangle.y = temp->getY();
            rectangle.w = temp->getWidth();
            rectangle.h = temp->getHeight();
            if (temp->next != NULL)
                temp = temp->next;
        } while (temp->next != NULL);
    }
    if (SDL_RenderFillRect(window->GetRenderer(), &rectangle) != 0)
        Utils::SDL_ExitWithError("RenderFillRect");
    SDL_RenderPresent(window->GetRenderer());
}

SDL_bool Menu::active(MainSDLWindow *window, Apple *apple, Snake *snake)
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
                    printf("X: %d\nY: %d\nW: %d\n H: %d\n\n", getX(), getY(), getWidth(), getHeight());
                    continue;

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
    return SDL_TRUE;
}