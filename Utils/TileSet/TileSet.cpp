#include "TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
{
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  tileSet = new Sprite(file, nullptr);
  if (tileSet == nullptr)
  {
    std::cout << "TileSet::TileSet: tileSet is nullptr" << std::endl;
    exit(1);
  }
  columns = tileSet->GetWidth() / tileWidth;
  rows = tileSet->GetHeight() / tileHeight;
  std::cout << "Criou Tileset" << std::endl;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
  if (index < rows * columns)
  {
    int tileX = (index % columns) * tileWidth;
    int tileY = (index / columns) * tileHeight;
    tileSet->SetClip(tileX, tileY, tileWidth, tileHeight);
    tileSet->Render(x, y);
  }
}

int TileSet::GetTileWidth()
{
  return tileWidth;
}

int TileSet::GetTileHeight()
{
  return tileHeight;
}
