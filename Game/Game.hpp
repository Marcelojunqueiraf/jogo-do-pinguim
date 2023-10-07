#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"
#include "../State/State.hpp"
#include <string>

class Game
{
private:
  static Game *instance;
  SDL_Renderer *renderer;
  SDL_Window *window;
  bool running;
  int frameStart;
  float dt;
  void CalculateDeltaTime();
  Game(std::string title, int width, int height);

public:
  static Game *getInstance();
  void run();
  SDL_Renderer *GetRenderer();
  int GetWidth();
  int GetHeight();
  ~Game();
};
