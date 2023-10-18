#include "Sprite.hpp"

Sprite::Sprite(std::weak_ptr<GameObject> associated) : Component(associated)
{
  texture = nullptr;
  scale = Vec2(1, 1);
}

Sprite::Sprite(std::string file, std::weak_ptr<GameObject> associated) : Component(associated)
{
  texture = nullptr;
  scale = Vec2(1, 1);
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
  if (!associated.expired())
  {
    associated.lock()->box.w = width / 2;
    associated.lock()->box.h = height / 2;
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
  dstrect.w = clipRect.w * scale.x;
  dstrect.h = clipRect.h * scale.y;
  float angle = associated.expired() ? 0 : associated.lock()->angle;
  angle = angle * 180 / M_PI;
  SDL_RenderCopyEx(Game::GetInstance()->GetRenderer().lock().get(), texture, &clipRect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth()
{
  return width * scale.x;
}

int Sprite::GetHeight()
{
  return height * scale.y;
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
  Render(this->associated.lock()->box.x, this->associated.lock()->box.y);
};

bool Sprite::Is(std::string type)
{
  return type == "Sprite";
}

void Sprite::Start()
{
}

void Sprite::SetScaleX(float scaleX, float scaleY)
{
  this->scale.x = scaleX;
  this->scale.y = scaleY;
  this->associated.lock()->box.w = this->width * scaleX;
  this->associated.lock()->box.h = this->height * scaleY;
}

Vec2 Sprite::GetScale()
{
  return this->scale;
}