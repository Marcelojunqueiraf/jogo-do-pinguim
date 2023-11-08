#include "./PenguinBody.hpp"

PenguinBody::PenguinBody(std::weak_ptr<GameObject> associated) : Component(associated)
{
  this->hp = 100;
  this->linearSpeed = 200;
  this->angle = 0;
  this->pcannon = std::weak_ptr<GameObject>();
  speed = Vec2(this->linearSpeed, 0);
  Camera &camera = Camera::GetInstance();
  camera.Follow(associated.lock().get());
}

void PenguinBody::Update(float dt)
{
  if (hp <= 0)
  {
    Camera::GetInstance().Unfollow();
    this->associated.lock()->RequestDelete();
    this->pcannon.lock()->RequestDelete();
  }
  // calculate speed using angle
  this->speed.x = this->linearSpeed * cos(this->angle);
  this->speed.y = this->linearSpeed * sin(this->angle);

  this->associated.lock()->angle = this->angle;
  this->associated.lock()->box.x += this->speed.x * dt;
  this->associated.lock()->box.y += this->speed.y * dt;

  InputManager &input = InputManager::GetInstance();
  // Change angle with a and d
  if (input.IsKeyDown(SDLK_a))
    angle -= 8 * M_1_PI * dt;
  if (input.IsKeyDown(SDLK_d))
    angle += 8 * M_1_PI * dt;
  if (input.IsKeyDown(SDLK_w) && linearSpeed < 300)
    linearSpeed += 100 * dt;
  if (input.IsKeyDown(SDLK_s) && linearSpeed >= 100 * dt)
    linearSpeed -= 100 * dt;
}

bool PenguinBody::Is(std::string type)
{
  return type == "PenguinBody";
}

void PenguinBody::SetPcannon(std::weak_ptr<GameObject> pcannon)
{
  this->pcannon = pcannon;
}

void PenguinBody::NotifyCollision(std::weak_ptr<GameObject> other)
{
  if (auto bulletPtr = other.lock()->GetComponent("Bullet").lock())
  {
    Bullet *bullet = (Bullet *)bulletPtr.get();
    if (bullet->targetPlayer)
    {
      this->hp -= bullet->GetDamage();
    }
  }
}