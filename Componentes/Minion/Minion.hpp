#pragma once
#include "../Component/Component.hpp"
#include <memory>
#include "../Sprite/Sprite.hpp"
#include "../../Game/Game.hpp"
#include "../Bullet/Bullet.hpp"

class Minion : public Component
{
public:
  Minion(std::weak_ptr<GameObject> associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
  void Update(float dt);
  bool Is(std::string type);
  void Shoot(Vec2 target);

private:
  std::weak_ptr<GameObject> alienCenter;
  float arc;
};