#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "../Component/Component.hpp"
#include "../../Utils/Vec2/Vec2.hpp"
#include "../../Utils/InputManager/InputManager.hpp"
#include "../Sprite/Sprite.hpp"

class Alien : public Component
{
private:
  class Action
  {
  public:
    enum ActionType
    {
      MOVE,
      SHOOT
    };
    Action(ActionType type, float x, float y) : type(type), pos(x, y) {}
    ActionType type;
    Vec2 pos;
  };

  Vec2 speed;
  int hp;
  std::vector<std::weak_ptr<GameObject>> minionArray;
  std::queue<Action> taskQueue;

public:
  Alien(GameObject *associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
