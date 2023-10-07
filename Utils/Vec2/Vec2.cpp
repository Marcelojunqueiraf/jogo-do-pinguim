#include "Vec2.hpp"

Vec2::Vec2(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vec2::Vec2()
{
  this->x = 0;
  this->y = 0;
}

Vec2 Vec2::operator+(Vec2 v)
{
  return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator-(Vec2 v)
{
  return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator*(float n)
{
  return Vec2(this->x * n, this->y * n);
}

Vec2 Vec2::operator/(float n)
{
  return Vec2(this->x / n, this->y / n);
}

float Vec2::magnitude()
{
  return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vec2 Vec2::normalize()
{
  float magnitude = this->magnitude();
  if (magnitude == 0)
    return Vec2(0, 0);
  return Vec2(this->x / magnitude, this->y / magnitude);
}