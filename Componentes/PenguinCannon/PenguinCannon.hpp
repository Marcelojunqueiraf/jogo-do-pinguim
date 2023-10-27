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
  void Update(float);
  bool Is(std::string);
  void Shoot();

private:
  std::weak_ptr<GameObject> pbody;
  float angle;
};