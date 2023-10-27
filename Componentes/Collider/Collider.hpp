#pragma once

#include "../Component/Component.hpp"
#include <memory>
#include "../../GameObject/GameObject.hpp"
#include "../../Utils/Vec2/Vec2.hpp"
#include "../../Utils/Rect/Rect.hpp"

class Collider : public Component
{
public:
  Collider(std::weak_ptr<GameObject> associated, Vec2 scale, Vec2 offset);
  Rect box;
  void Update(float dt);
  bool Is(std::string type);
  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);

private:
  Vec2 scale;
  Vec2 offset;
};