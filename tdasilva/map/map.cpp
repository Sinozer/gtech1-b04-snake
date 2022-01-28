#include <SDL2/SDL.h>

#include "map.hpp"
#include "../MainSDLWindow.hpp"

void Map::printMap(SDL_Renderer *renderer)
{
    int testColor = 0;
    for (int x = 2; x < (WINDOW_SIZE_X * CHUNK_SIZE_X) - 2; x += CHUNK_SIZE_X)
    {
        if (testColor == 0)
        {
            testColor = 1;
        }
        else{
            testColor = 0;
        }

        for (int y = 2; y < (WINDOW_SIZE_Y * CHUNK_SIZE_Y) - 2; y += CHUNK_SIZE_Y)
        {
            if (testColor == 0)
            {
                SDL_SetRenderDrawColor(renderer, 142, 204, 57, 1);
                testColor = 1;
            }
            else if (testColor == 1)
            {
                SDL_SetRenderDrawColor(renderer, 167, 217, 72, 1);
                testColor = 0;
            }

            SDL_Rect rectangle;
            rectangle.w = CHUNK_SIZE_X;
            rectangle.h = CHUNK_SIZE_Y;
            rectangle.x = x;
            rectangle.y = y;

            SDL_RenderFillRect(renderer, &rectangle);
        }
    }
}