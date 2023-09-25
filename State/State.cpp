#include "State.hpp"

State::State()
{
  quitRequested = false;
  objectArray = std::vector<GameObject *>();
  LoadAssets();
}

State::~State()
{
}

void State::LoadAssets()
{
  GameObject *go = new GameObject();
  this->objectArray.push_back(go);

  Sprite *bg = new Sprite("img/ocean.jpg", go);
  go->AddComponent(bg);
  music.Open("audio/stageState.ogg");
  music.Play();
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
    // mouse click
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      int mouseX = event.button.x;
      int mouseY = event.button.y;
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        // posicionar um objeto em uma posição aleatória em um circulo ao redor da posição do mouse
        float angulo = 0.01 * (rand() % 700);
        float raio = 150;
        float x = mouseX + raio * cos(angulo) - 50;
        float y = mouseY + raio * sin(angulo) - 50;
        this->AddObject(x, y);
      }
      else if (event.button.button == SDL_BUTTON_RIGHT)
      {
      }
    }
  }

  for (GameObject *go : objectArray)
  {
    go->Update(dt);
  }
}

void State::Render()
{
  for (GameObject *go : this->objectArray)
  {
    go->Render();
  }

  SDL_RenderPresent(Game::getInstance()->GetRenderer());
}

bool State::QuitRequested()
{
  return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
  GameObject *go = new GameObject();
  Sprite *sp = new Sprite("img/penguinface.png", go);
  go->AddComponent(sp);
  go->box.x = mouseX - go->box.w / 2;
  go->box.y = mouseY - go->box.h / 2;
  this->objectArray.push_back(go);
}