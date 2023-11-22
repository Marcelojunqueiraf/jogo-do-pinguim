#include "MenuState.hpp"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::LoadAssets()
{
  GameObject *go = new GameObject();
  std::weak_ptr<GameObject> goPtr = this->AddObject(go);
  Sprite *bg = new Sprite("Assets/img/title.jpg", goPtr);
  go->AddComponent(bg);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();
}

void MenuState::Update(float dt)
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
    StageState *gameStage = new StageState();
    Game::GetInstance()->SetCurrentState(gameStage);
    return;
  }

  UpdateArray(dt);
}

void MenuState::Render()
{
  RenderArray();
}

bool MenuState::QuitRequested()
{
  return quitRequested;
}

void MenuState::Start()
{
  LoadAssets();

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
