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
  Input();

  for (int i = 0; i < objectArray.size(); i++)
  {
    GameObject *go = objectArray[i];
    if (go->IsDead())
    {
      objectArray.erase(objectArray.begin() + i);
      delete go;
    }
    else
    {
      go->Update(dt);
    }
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
  go->box.w = sp->GetWidth();
  go->box.h = sp->GetHeight();

  Face *face = new Face(go);
  go->AddComponent(face);
  Sound *sound = new Sound("audio/boom.wav", go);
  go->AddComponent(sound);

  this->objectArray.push_back(go);
}

void State::Input()
{
  SDL_Event event;
  int mouseX, mouseY;

  while (SDL_PollEvent(&event))
  {
    SDL_GetMouseState(&mouseX, &mouseY);
    if (event.type == SDL_QUIT)
    {
      quitRequested = true;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {

      for (int i = objectArray.size() - 1; i >= 0; --i)
      {
        GameObject *go = objectArray[i];

        if (go->box.Contains((float)mouseX, (float)mouseY))
        {
          Face *face = (Face *)go->GetComponent("Face");
          if (nullptr != face)
          {
            face->Damage(10);
            break;
          }
        }
      }
    }
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        quitRequested = true;
      }
      else
      {
        float angulo = 0.01 * (rand() % 700);
        float raio = 150;
        float x = mouseX + raio * cos(angulo) - 50;
        float y = mouseY + raio * sin(angulo) - 50;
        this->AddObject(x, y);
      }
    }
  }
}