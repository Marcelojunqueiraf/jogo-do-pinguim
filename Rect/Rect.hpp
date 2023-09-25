#pragma once

class Rect
{
public:
  float x, y, w, h;
  Rect(float x, float y, float w, float h);
  Rect();
  bool Contains(float x, float y);
};