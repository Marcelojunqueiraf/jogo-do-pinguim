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
  GameObject *bulletGO = new GameObject();
  bulletGO->box.x = this->associated.lock()->box.GetCenter().x;
  bulletGO->box.y = this->associated.lock()->box.GetCenter().y;
  std::weak_ptr<GameObject> bulletPtr = Game::GetInstance()->GetCurrentState().lock()->AddObject(bulletGO);
  float angle = (target - this->associated.lock()->box.GetCenter()).getAngle();
  Bullet *bullet = new Bullet(bulletPtr, angle, 500, 10, 1000, "Assets/img/minionbullet1.png");
  bulletGO->AddComponent(bullet);
}

void Minion::Start()
{
}