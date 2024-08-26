#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.hpp"
#include "Constants.hpp"

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(Tile *tiles[]);

// Frees media and shuts down SDL
void close(Tile *tiles[]);

// Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

// Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile *tiles[]);

// Sets tiles from tile map
bool setTiles(Tile *tiles[]);
