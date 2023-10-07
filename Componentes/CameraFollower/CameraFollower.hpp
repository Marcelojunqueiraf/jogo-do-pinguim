#pragma once
#include "../Component/Component.hpp"
#include "../../Camera/Camera.hpp"
#include <string>
#include <iostream>

class CameraFollower : public Component
{
public:
  CameraFollower(GameObject *associated);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};