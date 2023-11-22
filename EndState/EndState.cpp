#include "EndState.hpp"

EndState::EndState()
{
}

EndState::~EndState()
{
}

void EndState::LoadAssets()
{
  GameObject *go = new GameObject();
  std::weak_ptr<GameObject> goPtr = this->AddObject(go);
  Sprite *bg = new Sprite("Assets/img/lose.jpg", goPtr);
  go->AddComponent(bg);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();
}

void EndState::Update(float dt)
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

void EndState::Render()
{
  RenderArray();
}

bool EndState::QuitRequested()
{
  return quitRequested;
}

void EndState::Start()
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
