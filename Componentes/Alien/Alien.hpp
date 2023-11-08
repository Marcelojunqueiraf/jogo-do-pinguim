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
#include "../Collider/Collider.hpp"
#include "../../Utils/Timer/Timer.hpp"

class Alien : public Component
{
public:
  Alien(std::weak_ptr<GameObject> associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  bool Is(std::string type);
  virtual void NotifyCollision(std::weak_ptr<GameObject> other);
  static int alienCount;

private:
  float speed;
  int hp;
  std::vector<std::weak_ptr<GameObject>> minionArray;
  enum AlienState
  {
    MOVING,
    RESTING
  };
  AlienState state;
  Timer restTimer;
  Vec2 destination;
};
