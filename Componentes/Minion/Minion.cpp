#include "./Minion.hpp"

#include <iostream>

Minion::Minion(std::weak_ptr<GameObject> associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter)
{
  this->arc = arcOffsetDeg;
  Sprite *minionSprite = new Sprite("Assets/img/minion.png", associated);
  float scale = (rand() % 50) / 100.0 + 1.0;
  minionSprite->SetScaleX(scale, scale);
  associated.lock()->AddComponent(minionSprite);
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
    this->associated.lock()->angle = this->arc + M_PI / 2;
  }
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
  Bullet *bullet = new Bullet(bulletPtr, angle, 500, 10, 1000, "Assets/img/minionbullet2.png");
  bulletGO->AddComponent(bullet);
}
