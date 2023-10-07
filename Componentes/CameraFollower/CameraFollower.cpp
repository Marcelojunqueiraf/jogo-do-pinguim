#include "./CameraFollower.hpp"

CameraFollower::CameraFollower(GameObject *associated) : Component(associated)
{
  std::cout << "CameraFollower" << std::endl;
}

void CameraFollower::Update(float dt)
{
  this->associated->box.x = Camera::GetInstance().pos.x;
  this->associated->box.y = Camera::GetInstance().pos.y;
}

void CameraFollower::Render()
{
}

bool CameraFollower::Is(std::string type)
{
  return type == "CameraFollower";
}