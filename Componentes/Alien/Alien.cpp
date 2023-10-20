#include "./Alien.hpp"

Alien::Alien(std::weak_ptr<GameObject> associated, int nMinions) : Component(associated)
{
  Sprite *alienSprite = new Sprite("Assets/img/alien.png", associated);
  associated.lock()->AddComponent(alienSprite);

  this->speed = 200;
  this->hp = 30;
  this->minionArray = std::vector<std::weak_ptr<GameObject>>();
  this->taskQueue = std::queue<Action>();

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

  // if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
  // {
  //   InputManager &input = InputManager::GetInstance();
  //   int x = input.GetMouseX() - this->associated.lock()->box.w / 2;
  //   int y = input.GetMouseY() - this->associated.lock()->box.h / 2;
  //   this->taskQueue.push(Action(Action::MOVE, x, y));
  // }

  // if (!this->taskQueue.empty())
  // {
  //   Action action = this->taskQueue.front();
  //   if (action.type == Action::ActionType::MOVE)
  //   {
  //     Vec2 dist = action.pos - this->associated.lock()->box.GetCenter();
  //     if (dist.magnitude() > this->speed * dt)
  //     {
  //       Vec2 velocity = dist.normalize() * this->speed;
  //       this->associated.lock()->box.x += velocity.x * dt;
  //       this->associated.lock()->box.y += velocity.y * dt;
  //     }
  //     else
  //     {
  //       this->taskQueue.pop();
  //     }
  //   }
  //   else if (action.type == Action::ActionType::SHOOT)
  //   {
  //     std::shared_ptr<GameObject> chosenMinion;
  //     float distance = 1000000;
  //     for (auto minion : this->minionArray)
  //     {
  //       std::shared_ptr<GameObject> minionPtr = minion.lock();
  //       if (minionPtr)
  //       {
  //         Vec2 minionPos = minionPtr->box.GetCenter();
  //         float minionDistance = (minionPos - action.pos).magnitude();
  //         if (minionDistance < distance)
  //         {
  //           distance = minionDistance;
  //           chosenMinion = minionPtr;
  //         }
  //       }
  //     }
  //     Minion *minionComponent = (Minion *)chosenMinion.get()->GetComponent("Minion").lock().get();
  //     if (minionComponent)
  //     {
  //       minionComponent->Shoot(action.pos);
  //     }
  //     this->taskQueue.pop();
  //   }
  // }

  // if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))
  // {
  //   InputManager &input = InputManager::GetInstance();
  //   int x = input.GetMouseX() - this->associated.lock()->box.w / 2;
  //   int y = input.GetMouseY() - this->associated.lock()->box.h / 2;
  //   this->taskQueue.push(Action(Action::ActionType::SHOOT, x, y));
  // }

  if (this->hp <= 0)
  {
    this->associated.lock()->RequestDelete();
  }
}

void Alien::Render()
{
}

bool Alien::Is(std::string type)
{
  return type == "Alien";
}