#include "State.hpp"

State::State()
{
  quitRequested = false;
  LoadAssets();
  music.Open("audio/stageState.ogg");
  music.Play();
}

State::~State()
{
}

void State::LoadAssets()
{
  bg.Open("img/ocean.jpg");
}

void State::Update(float dt)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      quitRequested = true;
    }
  }
}

void State::Render()
{
  bg.Render(0, 0);

  SDL_RenderPresent(Game::getInstance()->GetRenderer());
}

bool State::QuitRequested()
{
  return quitRequested;
}
