#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "../Component/Component.hpp"
#include "../../Utils/Vec2/Vec2.hpp"
#include "../../Utils/InputManager/InputManager.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Minion/Minion.hpp"

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

  float speed;
  int hp;
  std::vector<std::weak_ptr<GameObject>> minionArray;
  std::queue<Action> taskQueue;

public:
  Alien(std::weak_ptr<GameObject> associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  bool Is(std::string type);
};
