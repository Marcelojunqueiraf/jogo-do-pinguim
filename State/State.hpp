#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"
#include "../Sprite/Sprite.hpp"
#include "../Music/Music.hpp"
#include "../GameObject/GameObject.hpp"

class State
{
private:
  Music music;
  bool quitRequested;
  std::vector<GameObject *> objectArray;

public:
  State();
  ~State();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void AddObject(int mouseX, int mouseY);
};