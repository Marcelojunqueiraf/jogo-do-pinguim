#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "../../Game/Game.hpp"
#include "../Component/Component.hpp"
#include "../../GameObject/GameObject.hpp"
#include "../PenguinBody/PenguinBody.hpp"
#include "../Bullet/Bullet.hpp"
#include "../../Utils/InputManager/InputManager.hpp"

class PenguinCannon : public Component
{
public:
  PenguinCannon(std::weak_ptr<GameObject> associated, std::weak_ptr<GameObject> penguinBody);
  ~PenguinCannon();
  void Update(float);
  void Render();
  bool Is(std::string);
  void Shoot();
  void Start();

private:
  std::weak_ptr<GameObject> pbody;
  float angle;
};