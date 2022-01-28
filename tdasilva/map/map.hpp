#pragma once

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define MAP_SIZE_X 18
#define MAP_SIZE_Y 12
#define MAP_BORDER 4
#define START_X 2
#define START_Y 2
#define START_DIRECTION 'E'

#include <SDL2/SDL.h>

class Map
{
public:
    Map();
    void static printMap(SDL_Renderer *renderer);
};