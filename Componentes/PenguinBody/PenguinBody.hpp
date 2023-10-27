#pragma once

#include "../Component/Component.hpp"
#include "../../Utils/InputManager/InputManager.hpp"
#include "../../Camera/Camera.hpp"
#include <memory>

class PenguinBody : public Component
{
public:
  PenguinBody(std::weak_ptr<GameObject> associated);
  void Update(float dt);
  bool Is(std::string type);
  void SetPcannon(std::weak_ptr<GameObject> pcannon);

private:
  Vec2 speed;
  float linearSpeed;
  float angle;
  float hp;
  std::weak_ptr<GameObject> pcannon;
};