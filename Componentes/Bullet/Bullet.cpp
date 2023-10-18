#include "./Bullet.hpp"

Bullet::Bullet(std::weak_ptr<GameObject> associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated)
{
  this->speed = Vec2(speed, 0).rotate(angle);
  this->distanceLeft = maxDistance;
  this->damage = damage;
  this->associated.lock()->AddComponent(new Sprite(sprite, associated));
  // this->associated.lock()->AddComponent(new Collider(associated));
};

void Bullet::Update(float dt)
{
  this->distanceLeft -= this->speed.magnitude() * dt;
  if (this->distanceLeft <= 0)
  {
    this->associated.lock()->RequestDelete();
  }
  this->associated.lock()->box.x += this->speed.x * dt;
  this->associated.lock()->box.y += this->speed.y * dt;
}

void Bullet::Render()
{
}

bool Bullet::Is(std::string type)
{
  return type == "Bullet";
}

int Bullet::GetDamage()
{
  return this->damage;
}

void Bullet::Start()
{
}