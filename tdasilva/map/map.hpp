#pragma once

#include "../MainSDLWindow.hpp"

// DEF->Chunk: Chunk is an imaginary cell

#define CHUNK_SIZE_X 32          // Game board chunk size on X axis
#define CHUNK_SIZE_Y 32          // Game board chunk size on Y axis
#define MAP_SIZE_X WINDOW_SIZE_X // Game board size on X axis
#define MAP_SIZE_Y WINDOW_SIZE_Y // Game board size on Y axis
#define MAP_BORDER 4             // Border between window and game board (/2 for one side)
#define START_X 8                // Snake start pos on X axis
#define START_Y 6                // Snake start pos on Y axis
#define START_DIRECTION 'E'      // Default snake start direction

#include <SDL2/SDL.h>

class Map
{
public:
    Map();
    void static printMap(SDL_Renderer *renderer); // Print the map pattern
};