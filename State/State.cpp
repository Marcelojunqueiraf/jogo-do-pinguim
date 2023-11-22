#include "State.hpp"
#include "../Game/Game.hpp"
#include "../GameObject/GameObject.hpp"

State::State()
{
  this->popRequested = false;
  this->quitRequested = false;
  this->started = false;
}

State::~State()
{
  std::cout << "State destructor: " << objectArray.size() << std::endl;
  this->objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
  std::shared_ptr<GameObject> goPtr(go);
  this->objectArray.push_back(goPtr);
  if (this->started)
  {
    go->Start();
  }
  return goPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
  for (auto it = this->objectArray.begin(); it != this->objectArray.end(); it++)
  {
    if (it->get() == go)
    {
      return *it;
    }
  }
  return std::weak_ptr<GameObject>();
}

bool State::PopRequested()
{
  return this->popRequested;
}

bool State::QuitRequested()
{
  return this->quitRequested;
}

void State::StartArray()
{
  for (auto it = this->objectArray.begin(); it != this->objectArray.end(); it++)
  {
    it->get()->Start();
  }
}

void State::UpdateArray(float dt)
{
  for (int i = 0; i < objectArray.size(); i++)
  {
    std::weak_ptr<GameObject> go = objectArray[i];
    if (auto lock = go.lock())
    {
      if (lock->IsDead())
      {
        objectArray.erase(objectArray.begin() + i);
      }
      else
      {
        lock->Update(dt);
      }
    }
  }
}

void State::RenderArray()
{
  for (auto SharedGo : this->objectArray)
  {
    std::weak_ptr<GameObject> go = SharedGo;
    if (auto lock = go.lock())
      if (!lock->IsDead())
        lock->Render();
  }
  std::weak_ptr<SDL_Renderer> renderer = Game::GetInstance()->GetRenderer();
  SDL_RenderPresent(renderer.lock().get());
}
