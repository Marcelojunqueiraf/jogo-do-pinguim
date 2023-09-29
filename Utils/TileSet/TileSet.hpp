#pragma once
#include "../../Componentes/Sprite/Sprite.hpp"

class Sprite;

class TileSet
{
private:
  int tileWidth;
  int tileHeight;
  int rows;
  int columns;
  Sprite *tileSet;

public:
  TileSet(int tileWidth, int tileHeight, std::string file);
  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
};