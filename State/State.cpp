#include "State.hpp"

State::State()
{
  quitRequested = false;
  objectArray = std::vector<std::shared_ptr<GameObject>>();
}

State::~State()
{
}

void State::LoadAssets()
{
  GameObject *go = new GameObject();

  Sprite *bg = new Sprite("Assets/img/ocean.jpg", go);
  go->AddComponent(bg);

  CameraFollower *cameraFollower = new CameraFollower(go);
  go->AddComponent(cameraFollower);

  this->AddObject(go);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();

  GameObject *tileGo = new GameObject();
  TileMap *tileMap = new TileMap(tileGo, "Assets/map/tileMap.txt", new TileSet(64, 64, "Assets/img/tileset.png"));
  tileGo->AddComponent(tileMap);
  this->AddObject(tileGo);

  // Alien
  GameObject *alien = new GameObject();
  Alien *alienComponent = new Alien(alien, 4);
  alien->AddComponent(alienComponent);
  this->AddObject(alien);
}

void State::Update(float dt)
{
  InputManager &input = InputManager::GetInstance();
  input.Update();

  Camera::GetInstance().Update(dt);

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }

  for (int i = 0; i < objectArray.size(); i++)
  {
    std::weak_ptr<GameObject> go = objectArray[i];
    if (auto lock = go.lock())
    {
      if (lock->IsDead())
      {
        objectArray.erase(objectArray.begin() + i);
      }
      else
      {
        lock->Update(dt);
      }
    }
  }
}

void State::Render()
{
  for (auto SharedGo : this->objectArray)
  {
    std::weak_ptr<GameObject> go = SharedGo;
    if (auto lock = go.lock())
      lock->Render();
  }

  SDL_RenderPresent(Game::getInstance()->GetRenderer());
}

bool State::QuitRequested()
{
  return quitRequested;
}

void State::Start()
{
  LoadAssets();

  for (auto go : objectArray)
  {
    go->Start();
  }

  this->started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
  std::shared_ptr<GameObject> sharedGo(go);
  this->objectArray.push_back(sharedGo);
  if (started)
  {
    go->Start();
  }
  return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
  for (int i = 0; i < objectArray.size(); i++)
  {
    if (objectArray[i].get() == go)
    {
      return objectArray[i];
    }
  }
  return std::weak_ptr<GameObject>();
}
