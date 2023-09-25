#include "Game.hpp"
#include "../State/State.hpp"

#include <iostream>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height)
{
  Game::instance = this;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }

  if (IMG_Init((IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }

  if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
  {
    Mix_VolumeMusic(10);

    for (int i = 0; i < 32; i++)
    {
      Mix_Volume(i, 10);
    }

    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }

  run();
}

Game *Game::getInstance()
{
  if (Game::instance == NULL)
  {
    return new Game("Marcelo Junqueira 200023624", 1024, 600);
  }
  else
  {
    return instance;
  }
}

void Game::run()
{
  State *state = new State();

  bool running = true;
  while (running)
  {
    state->Update(33);
    state->Render();

    if (state->QuitRequested())
      running = false;
    SDL_Delay(33);
  }
}

SDL_Renderer *Game::GetRenderer()
{
  return renderer;
}

Game::~Game()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}