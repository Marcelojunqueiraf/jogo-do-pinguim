#include "Sound.hpp"

Sound::Sound(GameObject *associated) : Component(associated)
{
  this->chunk = nullptr;
}

Sound::Sound(std::string file, GameObject *associated) : Sound(associated)
{
  this->Open(file);
}

Sound::~Sound()
{
  if (this->chunk != nullptr)
  {
    Mix_HaltChannel(this->channel);
    Mix_FreeChunk(this->chunk);
  }
}

void Sound::Play(int times)
{
  this->channel = Mix_PlayChannel(-1, this->chunk, times - 1);
}

void Sound::Stop()
{
  Mix_HaltChannel(this->channel);
}

void Sound::Open(std::string file)
{
  this->chunk = Mix_LoadWAV(file.c_str());
  if (this->chunk == nullptr)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }
}

bool Sound::IsOpen()
{
  return this->chunk != nullptr;
}

void Sound::Update(float dt)
{
}

void Sound::Render()
{
}

bool Sound::Is(std::string type)
{
  return type == "Sound";
}