#pragma once

#include "../State/State.hpp"
#include "../Music/Music.hpp"
#include "../Componentes/Sound/Sound.hpp"
#include "../Utils/InputManager/InputManager.hpp"
#include "../StageState/StageState.hpp"

class MenuState : public State
{
private:
  Music music;

public:
  MenuState();
  ~MenuState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  bool QuitRequested();
  void Start();
};