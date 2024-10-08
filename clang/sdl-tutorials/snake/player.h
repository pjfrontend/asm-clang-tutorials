#ifndef PLAYER_H
#define PLAYER_h

#include "snake.h"
#include <SDL2/SDL.h>

class Player
{
public:
  Player(const Snake *snake, const SDL_Point *food);
  ~Player();
  void play(); // Play a single step of the game

private:
  const Snake *_snake;
  const SDL_Point *_food;
};

#endif