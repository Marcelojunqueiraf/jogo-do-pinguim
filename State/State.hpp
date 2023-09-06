#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"
#include "../Sprite/Sprite.hpp"
#include "../Music/Music.hpp"

class State
{
private:
  Sprite bg;
  Music music;
  bool quitRequested;

public:
  State();
  ~State();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
};