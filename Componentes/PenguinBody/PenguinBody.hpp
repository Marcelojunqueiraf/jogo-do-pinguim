#pragma once

#include "../Component/Component.hpp"
#include "../../Utils/InputManager/InputManager.hpp"
#include "../../Camera/Camera.hpp"
#include <memory>

class PenguinBody : public Component
{
public:
  PenguinBody(std::weak_ptr<GameObject> associated);
  ~PenguinBody();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Start();
  void SetPcannon(std::weak_ptr<GameObject> pcannon);

private:
  Vec2 speed;
  float linearSpeed;
  float angle;
  float hp;
  std::weak_ptr<GameObject> pcannon;
};