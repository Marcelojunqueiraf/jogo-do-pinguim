#pragma once

#include "../State/State.hpp"
#include "../Componentes/Sprite/Sprite.hpp"
#include "../Music/Music.hpp"
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
#include "../WinState/WinState.hpp"
#include "../EndState/EndState.hpp"
#include "../Utils/Timer/Timer.hpp"

class StageState : public State
{
private:
  Timer alienTimer;
  Music music;

public:
  StageState();
  ~StageState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void Start();
};