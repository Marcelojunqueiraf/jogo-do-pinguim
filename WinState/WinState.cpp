#include "WinState.hpp"

WinState::WinState()
{
}

WinState::~WinState()
{
}

void WinState::LoadAssets()
{
  GameObject *go = new GameObject();
  std::weak_ptr<GameObject> goPtr = this->AddObject(go);
  Sprite *bg = new Sprite("Assets/img/win.jpg", goPtr);
  go->AddComponent(bg);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();
}

void WinState::Update(float dt)
{
  InputManager &input = InputManager::GetInstance();
  input.Update();

  Camera::GetInstance().Update(dt);

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }

  if (input.KeyPress(SDLK_SPACE))
  {
    MenuState *menuState = new MenuState();
    Game::GetInstance()->SetCurrentState(menuState);
    return;
  }

  UpdateArray(dt);
}

void WinState::Render()
{
  RenderArray();
}

bool WinState::QuitRequested()
{
  return quitRequested;
}

void WinState::Start()
{

  for (int i = 0; i < objectArray.size(); i++)
  {
    std::weak_ptr<GameObject> go = objectArray[i];
    if (auto lock = go.lock())
    {
      lock->Start();
    }
  }

  this->started = true;
}
