#pragma once
#include <SDL2/SDL.h>
#include "LTexture.hpp"
#include "Constants.hpp"

// The window we'll be rendering to
extern SDL_Window *gWindow;

// The window renderer
extern SDL_Renderer *gRenderer;

// Scene textures
extern LTexture gDotTexture;
extern LTexture gTileTexture;
extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];