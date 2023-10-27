#pragma once
#include "../Component/Component.hpp"
#include "../../Camera/Camera.hpp"
#include <string>
#include <iostream>

class CameraFollower : public Component
{
public:
  CameraFollower(std::weak_ptr<GameObject> associated);
  void Update(float dt);
  bool Is(std::string type);
};