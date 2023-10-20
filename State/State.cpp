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
  std::weak_ptr<GameObject> goPtr = this->AddObject(go);
  Sprite *bg = new Sprite("Assets/img/ocean.jpg", goPtr);
  go->AddComponent(bg);

  CameraFollower *cameraFollower = new CameraFollower(goPtr);
  go->AddComponent(cameraFollower);

  music.Open("Assets/audio/stageState.ogg");
  music.Play();

  GameObject *tileGo = new GameObject();
  std::weak_ptr<GameObject> tileGoPtr = this->AddObject(tileGo);
  TileMap *tileMap = new TileMap(tileGoPtr, "Assets/map/tileMap.txt", new TileSet(64, 64, "Assets/img/tileset.png"));
  tileGo->AddComponent(tileMap);
  this->AddObject(tileGo);

  // Alien

  GameObject *alien = new GameObject();
  std::weak_ptr<GameObject> alienPtr = this->AddObject(alien);
  Alien *alienComponent = new Alien(alienPtr, 4);
  alien->AddComponent(alienComponent);

  // Pinguim
  GameObject *penguin = new GameObject();
  std::weak_ptr<GameObject> penguinPtr = this->AddObject(penguin);
  PenguinBody *penguinBody = new PenguinBody(penguinPtr);
  penguin->AddComponent(penguinBody);
  Sprite *penguinSprite = new Sprite("Assets/img/penguin.png", penguinPtr);
  penguin->AddComponent(penguinSprite);

  GameObject *penguinCannon = new GameObject();
  std::weak_ptr<GameObject> penguinCannonPtr = this->AddObject(penguinCannon);
  PenguinCannon *penguinCannonComponent = new PenguinCannon(penguinCannonPtr, penguinPtr);
  penguinCannon->AddComponent(penguinCannonComponent);
  Sprite *penguinCannonSprite = new Sprite("Assets/img/cubngun.png", penguinCannonPtr);
  penguin->AddComponent(penguinCannonSprite);
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
      if (!lock->IsDead())
        lock->Render();
  }
  std::weak_ptr<SDL_Renderer> renderer = Game::GetInstance()->GetRenderer();
  SDL_RenderPresent(renderer.lock().get());
}

bool State::QuitRequested()
{
  return quitRequested;
}

void State::Start()
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

std::weak_ptr<GameObject> State::AddObject(GameObject *go)
{
  std::shared_ptr<GameObject> sharedPtr(go);
  this->objectArray.push_back(sharedPtr);
  if (started)
  {
    go->Start();
  }
  return std::weak_ptr<GameObject>(objectArray.back());
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
