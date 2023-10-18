#include "TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
{
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;

  tileSet = new Sprite(file, std::weak_ptr<GameObject>());
  if (tileSet == nullptr)
  {
    std::cout << "TileSet::TileSet: tileSet is nullptr" << std::endl;
    exit(1);
  }
  columns = tileSet->GetWidth() / tileWidth;
  rows = tileSet->GetHeight() / tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
  if (index >= 0 && index < rows * columns)
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
