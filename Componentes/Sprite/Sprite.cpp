#include "Sprite.hpp"

Sprite::Sprite(GameObject *associated) : Component(associated)
{
  texture = nullptr;
}

Sprite::Sprite(std::string file, GameObject *associated) : Component(associated)
{
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string file)
{
  if (texture != nullptr)
  {
    SDL_DestroyTexture(texture);
  }
  texture = Resources::GetImage(file);
  if (texture == nullptr)
  {
    std::cerr << SDL_GetError() << std::endl;
    std::terminate();
  }
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width, height);
  if (associated != nullptr)
  {
    associated->box.w = width / 2;
    associated->box.h = height / 2;
  }
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
  SDL_Rect dstrect;
  Camera &camera = Camera::GetInstance();
  dstrect.x = x - camera.pos.x;
  dstrect.y = y - camera.pos.y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;
  SDL_RenderCopy(Game::getInstance()->GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth()
{
  return width;
}

int Sprite::GetHeight()
{
  return height;
}

bool Sprite::IsOpen()
{
  return texture != nullptr;
}

void Sprite::Update(float dt)
{
}

void Sprite::Render()
{
  Render(this->associated->box.x, this->associated->box.y);
};

bool Sprite::Is(std::string type)
{
  return type == "Sprite";
}

void Sprite::Start()
{
}