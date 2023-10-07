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

  Sprite *bg = new Sprite("Assets/img/ocean.jpg", go);
  go->AddComponent(bg);

  CameraFollower *cameraFollower = new CameraFollower(go);
  go->AddComponent(cameraFollower);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();

  GameObject *tileGo = new GameObject();
  this->objectArray.push_back(tileGo);
  TileMap *tileMap = new TileMap(tileGo, "Assets/map/tileMap.txt", new TileSet(64, 64, "Assets/img/tileset.png"));
  tileGo->AddComponent(tileMap);
}

void State::Update(float dt)
{
  InputManager &input = InputManager::GetInstance();
  input.Update();

  Camera::GetInstance().Update(dt);

  if (input.KeyPress(SDLK_SPACE))
  {
    float angulo = 0.01 * (rand() % 700);
    float raio = 150;
    float x = input.GetMouseX() + raio * cos(angulo) - 50;
    float y = input.GetMouseY() + raio * sin(angulo) - 50;
    this->AddObject(x, y);
  }

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }

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
  Sprite *sp = new Sprite("Assets/img/penguinface.png", go);
  go->AddComponent(sp);
  go->box.x = mouseX - go->box.w / 2;
  go->box.y = mouseY - go->box.h / 2;
  go->box.w = sp->GetWidth();
  go->box.h = sp->GetHeight();

  Face *face = new Face(go);
  go->AddComponent(face);
  Sound *sound = new Sound("Assets/audio/boom.wav", go);
  go->AddComponent(sound);

  this->objectArray.push_back(go);
}
