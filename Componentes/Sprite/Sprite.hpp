#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../../SDL_include.h"
#include "../../Game/Game.hpp"
#include "../../GameObject/GameObject.hpp"
#include <iostream>

class Sprite : public Component
{
private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite(GameObject *associated);
  Sprite(std::string file, GameObject *associated);
  ~Sprite();
  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);

  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  bool IsOpen();

  void Update(float dt);
  void Render();
  bool Is(std::string type);
};