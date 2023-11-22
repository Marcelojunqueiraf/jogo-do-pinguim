#pragma once

#include "../State/State.hpp"
#include "../Music/Music.hpp"
#include "../Componentes/Sound/Sound.hpp"
#include "../Utils/InputManager/InputManager.hpp"
#include "../MenuState/MenuState.hpp"

class EndState : public State
{
private:
  Music music;

public:
  EndState();
  ~EndState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void Start();
};