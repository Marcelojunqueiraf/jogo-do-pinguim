#include "Face.hpp"
#include <iostream>

Face::Face(GameObject *associated) : Component(associated)
{
  this->hitpoints = 30;
}

Face::~Face()
{
}

void Face::Damage(int damage)
{
  this->hitpoints -= damage;

  Sound *sound = (Sound *)this->associated->GetComponent("Sound");
  if (sound != nullptr)
  {
    sound->Play();
  }

  if (this->hitpoints <= 0)
  {
    this->associated->RequestDelete();
  }
}

void Face::Update(float dt)
{
  InputManager &input = InputManager::GetInstance();

  if (input.MousePress(LEFT_MOUSE_BUTTON))
  {
    if (this->associated->box.Contains((float)input.GetMouseX(), (float)input.GetMouseY()))
    {
      this->Damage(10);
    }
  }
}

void Face::Render()
{
}

bool Face::Is(std::string type)
{
  return type == "Face";
}