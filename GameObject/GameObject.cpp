#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject()
{
  this->isDead = false;
  this->box = Rect();
  this->components = std::vector<Component *>();
}

GameObject::~GameObject()
{
  this->components.clear();
}

void GameObject::Update(float dt)
{
  if (this->IsDead())
  {
    for (Component *component : this->components)
    {
      delete component;
    }
    this->components.clear();
  }

  for (Component *component : this->components)
  {
    component->Update(dt);
  }
}

void GameObject::Render()
{
  for (Component *component : this->components)
  {
    component->Render();
  }
}

bool GameObject::IsDead()
{
  return this->isDead;
}

void GameObject::RequestDelete()
{
  this->isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
  this->components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
  for (Component *component : this->components)
  {
    if (component == cpt)
    {
      this->components.erase(this->components.begin() + (component - this->components[0]));
    }
  }
}

Component *GameObject::GetComponent(std::string type)
{
  for (int i = 0; i < this->components.size(); i++)
  {
    if (this->components[i]->Is(type))
    {
      return this->components[i];
    }
  }
  return nullptr;
}