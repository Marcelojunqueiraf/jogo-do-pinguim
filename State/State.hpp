#pragma once

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../SDL_include.h"

#include <memory>
#include <vector>

class Game;
class GameObject;

class State
{
public:
  State();
  ~State();
  virtual void LoadAssets() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;

  virtual void Start() = 0;

  std::weak_ptr<GameObject> AddObject(GameObject *go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);

  bool PopRequested();
  bool QuitRequested();

protected:
  void StartArray();
  virtual void UpdateArray(float dt);
  virtual void RenderArray();

  bool popRequested;
  bool quitRequested;
  bool started;

  std::vector<std::shared_ptr<GameObject>> objectArray;
};