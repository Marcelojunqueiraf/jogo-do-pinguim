#include "PenguinCannon.hpp"

PenguinCannon::PenguinCannon(std::weak_ptr<GameObject> associated, std::weak_ptr<GameObject> penguinBody) : Component(associated)
{
  this->pbody = penguinBody;
  this->angle = 0;
  PenguinBody *penguinBodyPtr = (PenguinBody *)penguinBody.lock()->GetComponent("PenguinBody").lock().get();
  penguinBodyPtr->SetPcannon(associated);
}

PenguinCannon::~PenguinCannon()
{
}

void PenguinCannon::Update(float dt)
{
  InputManager &inputManager = InputManager::GetInstance();

  this->angle = atan2(inputManager.GetMouseY() - (this->associated.lock()->box.GetCenter().y), inputManager.GetMouseX() - (this->associated.lock()->box.GetCenter().x));
  this->associated.lock()->angle = this->angle;

  this->associated.lock()->box.x = this->pbody.lock()->box.x + this->pbody.lock()->box.w / 2 - this->associated.lock()->box.w / 2;
  this->associated.lock()->box.y = this->pbody.lock()->box.y + this->pbody.lock()->box.h / 2 - this->associated.lock()->box.h / 2;

  InputManager &input = InputManager::GetInstance();

  if (input.MousePress(LEFT_MOUSE_BUTTON))
  {
    Shoot();
  }
}

void PenguinCannon::Render()
{
}

bool PenguinCannon::Is(std::string type)
{
  return type == "PenguinCannon";
}

void PenguinCannon::Shoot()
{
  GameObject *bulletGO = new GameObject();
  bulletGO->box.x = this->associated.lock()->box.GetCenter().x;
  bulletGO->box.y = this->associated.lock()->box.GetCenter().y;
  std::weak_ptr<GameObject> bulletPtr = Game::GetInstance()->GetCurrentState().lock()->AddObject(bulletGO);
  Bullet *bullet = new Bullet(bulletPtr, this->angle, 500, 10, 1000, "Assets/img/penguinbullet.png");
  bulletGO->AddComponent(bullet);
}

void PenguinCannon::Start()
{
}