#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"

#include <memory>
#include <vector>

#include "../Componentes/Sprite/Sprite.hpp"
#include "../Music/Music.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Utils/Vec2/Vec2.hpp"
#include "../Utils/Rect/Rect.hpp"
#include "../Componentes/Sound/Sound.hpp"
#include "../Componentes/TileMap/TileMap.hpp"
#include "../Componentes/CameraFollower/CameraFollower.hpp"
#include "../Componentes/Alien/Alien.hpp"
#include "../Utils/InputManager/InputManager.hpp"
#include "../Camera/Camera.hpp"
#include "../Componentes/PenguinBody/PenguinBody.hpp"
#include "../Componentes/PenguinCannon/PenguinCannon.hpp"
#include "../Componentes/Collider/Collider.hpp"
#include "../Utils/Collision/Collision.cpp"
#include "../Componentes/Collider/Collider.hpp"

class State
{
private:
  Music music;
  bool quitRequested;
  bool started;
  std::vector<std::shared_ptr<GameObject>> objectArray;

public:
  State();
  ~State();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void Start();
  std::weak_ptr<GameObject> AddObject(GameObject *go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);
};