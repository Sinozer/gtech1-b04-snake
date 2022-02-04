#pragma once

#include "../MainSDLWindow.hpp"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define MAP_SIZE_X WINDOW_SIZE_X
#define MAP_SIZE_Y WINDOW_SIZE_Y
#define MAP_BORDER 4
#define START_X 8
#define START_Y 6
#define START_DIRECTION 'E'

#include <SDL2/SDL.h>

class Map
{
public:
    Map();
    void static printMap(SDL_Renderer *renderer);
};