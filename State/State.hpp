#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"
#include "../Sprite/Sprite.hpp"
#include "../Music/Music.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Vec2/Vec2.hpp"
#include "../Rect/Rect.hpp"
#include "../Face/Face.hpp"
#include "../Sound/Sound.hpp"

class State
{
private:
  Music music;
  bool quitRequested;
  std::vector<GameObject *> objectArray;
  void Input();

public:
  State();
  ~State();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void AddObject(int mouseX, int mouseY);
};