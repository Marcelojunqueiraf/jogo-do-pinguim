#include "./Alien.hpp"

int Alien::alienCount = 0;

Alien::Alien(std::weak_ptr<GameObject> associated, int nMinions) : Component(associated)
{
  Sprite *alienSprite = new Sprite("Assets/img/alien.png", associated);
  associated.lock()->AddComponent(alienSprite);

  Collider *alienCollider = new Collider(associated, {1, 2});
  associated.lock()->AddComponent(alienCollider);

  this->speed = 200;
  this->hp = 30;
  this->minionArray = std::vector<std::weak_ptr<GameObject>>();
  this->state = AlienState::RESTING;
  restTimer = Timer();
  this->destination = Vec2(0, 0);
  std::cout << "Alien constructor" << std::endl;
  Alien::alienCount += 1;

  for (int i = 0; i < nMinions; i++)
  {
    GameObject *minionGO = new GameObject();

    std::weak_ptr<GameObject> minionPtr = Game::GetInstance()->GetCurrentState().lock()->AddObject(minionGO);
    this->minionArray.push_back(minionPtr);
    Minion *minion = new Minion(minionPtr, associated, i * (2 * M_PI / nMinions));
    minionGO->AddComponent(minion);
  }
}

Alien::~Alien()
{
  this->minionArray.clear();
}

void Alien::Start()
{
  for (int i = 0; i < this->minionArray.size(); i++)
  {
    std::shared_ptr<GameObject> minionPtr = this->minionArray[i].lock();
    if (minionPtr)
    {
      minionPtr->box.x = this->associated.lock()->box.x + (i * 110);
      minionPtr->box.y = this->associated.lock()->box.y;
    }
  }
}

void Alien::Update(float dt)
{
  this->associated.lock()->angle -= 0.2 * M_PI * dt;

  this->restTimer.Update(dt);

  if (state == AlienState::RESTING && this->restTimer.Get() > 1)
  {
    this->state = AlienState::MOVING;
    this->destination = Camera::GetInstance().pos;
    destination.x += 512;
    destination.y += 300;
  }
  else if (state == AlienState::MOVING && (this->destination - this->associated.lock()->box.GetCenter()).magnitude() < 6)
  {
    std::shared_ptr<GameObject> chosenMinion;
    float distance = 1000000;
    for (auto minion : this->minionArray)
    {
      std::shared_ptr<GameObject> minionPtr = minion.lock();
      if (minionPtr)
      {
        Vec2 minionPos = minionPtr->box.GetCenter();
        float minionDistance = (minionPos - destination).magnitude();
        if (minionDistance < distance)
        {
          distance = minionDistance;
          chosenMinion = minionPtr;
        }
      }
    }
    Minion *minionComponent = (Minion *)chosenMinion.get()->GetComponent("Minion").lock().get();
    if (minionComponent)
    {
      this->destination = Camera::GetInstance().pos;
      destination.x += 512;
      destination.y += 300;
      minionComponent->Shoot(destination);
    }

    this->state = AlienState::RESTING;
    this->restTimer.Restart();
  }
  if (state == AlienState::MOVING)
  {
    Vec2 dist = destination - this->associated.lock()->box.GetCenter();
    Vec2 velocity = dist.normalize() * this->speed;
    this->associated.lock()->box.x += velocity.x * dt;
    this->associated.lock()->box.y += velocity.y * dt;
  }
  if (this->hp <= 0)
  {
    Alien::alienCount -= 1;
    this->associated.lock()->RequestDelete();
  }
}

bool Alien::Is(std::string type)
{
  return type == "Alien";
}

void Alien::NotifyCollision(std::weak_ptr<GameObject> other)
{
  if (auto bulletPtr = other.lock()->GetComponent("Bullet").lock())
  {
    Bullet *bullet = (Bullet *)bulletPtr.get();
    if (!bullet->targetPlayer)
    {
      this->hp -= bullet->GetDamage();
    }
  }
}