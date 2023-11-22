#include "StageState.hpp"

class PenguinBody;

StageState::StageState()
{
  alienTimer = Timer();
}

StageState::~StageState()
{
  std::cout << "running destructor" << std::endl;
}

void StageState::LoadAssets()
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

  // Alien
  std::cout << "criando alien" << std::endl;
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
  Collider *collider = new Collider(penguinPtr, {1, 2});
  penguin->AddComponent(collider);

  GameObject *penguinCannon = new GameObject();
  std::weak_ptr<GameObject> penguinCannonPtr = this->AddObject(penguinCannon);
  PenguinCannon *penguinCannonComponent = new PenguinCannon(penguinCannonPtr, penguinPtr);
  penguinCannon->AddComponent(penguinCannonComponent);
  Sprite *penguinCannonSprite = new Sprite("Assets/img/cubngun.png", penguinCannonPtr);
  penguin->AddComponent(penguinCannonSprite);
}

void StageState::Update(float dt)
{
  std::cout << "aliens: " << Alien::alienCount << std::endl;
  if (Alien::alienCount <= 0)
  {
    WinState *winState = new WinState();
    Game::GetInstance()->SetCurrentState(winState);
    std::cout << "state criado" << std::endl;
    return;
  }

  InputManager &input = InputManager::GetInstance();
  input.Update();

  Camera::GetInstance().Update(dt);

  if (alienTimer.Get() > 1)
  {
    std::cout << "criando alien" << std::endl;
    GameObject *alien = new GameObject();
    std::weak_ptr<GameObject> alienPtr = this->AddObject(alien);
    Alien *alienComponent = new Alien(alienPtr, 4);
    alien->AddComponent(alienComponent);
    alienTimer.Restart();
  }
  alienTimer.Update(dt);

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
  {
    quitRequested = true;
  }

  // Verificar se existe um pinguim
  bool playerAlive = false;
  for (auto gameObject : this->objectArray)
  {
    if (gameObject->GetComponent("PenguinBody").lock() != nullptr)
    {
      playerAlive = true;
    }
  }

  if (!playerAlive)
  {
    EndState *endState = new EndState();
    Game::GetInstance()->SetCurrentState(endState);
    return;
  }

  // CHECK colision
  for (int i = 0; i < objectArray.size(); i++)
  {
    std::weak_ptr<GameObject> go = objectArray[i];
    if (auto lock = go.lock())
    {
      for (int j = i + 1; j < objectArray.size(); j++)
      {
        if (i == j)
          continue;
        std::weak_ptr<GameObject> other = objectArray[j];
        if (auto lockOther = other.lock())
        {
          std::weak_ptr<Component> collider = lock->GetComponent("Collider");
          std::weak_ptr<Component> otherCollider = lockOther->GetComponent("Collider");
          if (auto lockCollider = collider.lock())
          {
            if (auto lockOtherCollider = otherCollider.lock())
            {
              Collider *colliderComponent = (Collider *)lockCollider.get();
              Collider *otherColliderComponent = (Collider *)lockOtherCollider.get();
              if (Collision::IsColliding(colliderComponent->box, otherColliderComponent->box, lock->angle, lockOther->angle))
              {
                lock->NotifyCollision(other);
                lockOther->NotifyCollision(go);
              }
            }
          }
        }
      }
    }
  }

  UpdateArray(dt);
}

void StageState::Render()
{
  RenderArray();
}

bool StageState::QuitRequested()
{
  return quitRequested;
}

void StageState::Start()
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
