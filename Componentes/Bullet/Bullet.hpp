#pragma once

#include <memory>
#include "../../GameObject/GameObject.hpp"
#include <string>
#include <iostream>
#include "../../Utils/Vec2/Vec2.hpp"
#include "../Component/Component.hpp"
#include "../Sprite/Sprite.hpp"
// #include "../../Component/Collider/Collider.hpp"

class Bullet : public Component
{
public:
  Bullet(std::weak_ptr<GameObject> associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Start();
  int GetDamage();

private:
  Vec2 speed;
  float distanceLeft;
  int damage;
};