#pragma once
#include <vector>
#include <string>
#include "../Componentes/Component/Component.hpp"
#include "../Utils/Rect/Rect.hpp"

class Component;

class GameObject
{
private:
  bool isDead;
  bool started;
  std::vector<Component *> components;

public:
  Rect box;
  GameObject();
  ~GameObject();
  void Start();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *cpt);
  void RemoveComponent(Component *cpt);
  Component *GetComponent(std::string type);
};