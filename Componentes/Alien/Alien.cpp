#include "./Alien.hpp"

Alien::Alien(GameObject *associated, int nMinions) : Component(associated)
{
  Sprite *alienSprite = new Sprite("Assets/img/alien.png", associated);
  associated->AddComponent(alienSprite);

  this->speed = Vec2(100, 0);
  this->hp = 30;
  this->minionArray = std::vector<std::weak_ptr<GameObject>>();
  this->taskQueue = std::queue<Action>();
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
      minionPtr->box.x = this->associated->box.x + (i * 110);
      minionPtr->box.y = this->associated->box.y;
    }
  }
}

void Alien::Update(float dt)
{
  if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
  {
    InputManager &input = InputManager::GetInstance();
    int x = input.GetMouseX() - this->associated->box.w / 2;
    int y = input.GetMouseY() - this->associated->box.h / 2;
    this->taskQueue.push(Action(Action::MOVE, x, y));
  }

  if (!this->taskQueue.empty())
  {
    Action action = this->taskQueue.front();
    if (action.type == Action::ActionType::MOVE)
    {
      Vec2 dist = action.pos - this->associated->box.GetCenter();
      if (dist.magnitude() > 100 * dt)
      {
        Vec2 velocity = dist.normalize() * 100;
        this->associated->box.x += velocity.x * dt;
        this->associated->box.y += velocity.y * dt;
      }
      else
      {
        this->taskQueue.pop();
      }
    }
    else if (action.type == Action::ActionType::SHOOT)
    {
      std::cout << "tiro" << std::endl;
      this->taskQueue.pop();
    }
  }

  if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))
  {
    this->taskQueue.push(Action(Action::ActionType::SHOOT, 0, 0));
  }

  if (this->hp <= 0)
  {
    this->associated->RequestDelete();
  }
}

void Alien::Render()
{
}

bool Alien::Is(std::string type)
{
  return type == "Alien";
}