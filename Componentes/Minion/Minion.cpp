#include "./Minion.hpp"

#include <iostream>

Minion::Minion(std::weak_ptr<GameObject> associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter)
{
  this->arc = arcOffsetDeg;
  Sprite *minionSprite = new Sprite("Assets/img/minion.png", associated);
  associated.lock()->AddComponent(minionSprite);
}

Minion::~Minion()
{
}

void Minion::Update(float dt)
{
  if (this->alienCenter.expired())
  {
    this->associated.lock()->RequestDelete();
  }
  else
  {
    Vec2 center = this->alienCenter.lock()->box.GetCenter();
    this->arc += 0.5 * M_PI * dt;
    this->associated.lock()->box.x = center.x + 150 * std::cos(this->arc);
    this->associated.lock()->box.y = center.y + 150 * std::sin(this->arc);
  }
}

void Minion::Render()
{
}

bool Minion::Is(std::string type)
{
  return (type == "Minion");
}

void Minion::Shoot(Vec2 target)
{
  // GameObject *bulletGO = new GameObject();
  // bulletGO->box.x = this->associated->box.x;
  // bulletGO->box.y = this->associated->box.y;
  // Bullet *bullet = new Bullet(bulletGO, target, 200, 10, "assets/img/minionbullet2.png", 3, 0.1, true);
  // bulletGO->AddComponent(bullet);
  // Game::GetInstance()->)->GetCurrentState().AddObject(bulletGO);
}

void Minion::Start()
{
}