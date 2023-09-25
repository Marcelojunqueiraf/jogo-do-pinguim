#pragma once
#include <vector>
#include <string>
#include "../Component/Component.hpp"
#include "../Rect/Rect.hpp"

class Component;

class GameObject
{
private:
  bool isDead;
  std::vector<Component *> components;

public:
  Rect box;
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  Component *GetComponent(std::string type);
};