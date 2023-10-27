#include "Collider.hpp"

Collider::Collider(std::weak_ptr<GameObject> associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0}) : Component(associated)
{
  this->scale = scale;
  this->offset = offset;
}

void Collider::Update(float dt)
{
  if (auto sharedPtr = associated.lock())
  {
    this->box = Rect(sharedPtr->box.x + this->offset.x, sharedPtr->box.y + this->offset.y, sharedPtr->box.w * scale.x, sharedPtr->box.h * scale.y);
  }
  else
  {
    this->box = Rect(0, 0, 0, 0);
  }
}

bool Collider::Is(std::string type)
{
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale)
{
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
  this->offset = offset;
}
