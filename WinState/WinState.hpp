#pragma once

#include "../State/State.hpp"
#include "../Music/Music.hpp"
#include "../Componentes/Sound/Sound.hpp"
#include "../Utils/InputManager/InputManager.hpp"
#include "../MenuState/MenuState.hpp"

class WinState : public State
{
private:
  Music music;

public:
  WinState();
  ~WinState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void Start();
};