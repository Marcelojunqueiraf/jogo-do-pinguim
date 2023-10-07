#include "TileMap.hpp"
#include <fstream>

TileMap::TileMap(GameObject *associated, std::string file, TileSet *tileSet) : Component(associated)
{
  std::cout << "Criando TileMap" << std::endl;
  this->tileSet = tileSet;
  Load(file);
}

void TileMap::Load(std::string file)
{
  std::ifstream tileMapFile(file);
  if (tileMapFile.is_open())
  {
    std::string line;
    std::getline(tileMapFile, line, ',');
    mapWidth = std::stoi(line);

    std::getline(tileMapFile, line, ',');
    std::cout << "line: " << line << std::endl;
    mapHeight = std::stoi(line);

    std::getline(tileMapFile, line, ',');
    std::cout << "line: " << line << std::endl;
    mapDepth = std::stoi(line);

    std::getline(tileMapFile, line, ',');

    int tileNumber;
    while (std::getline(tileMapFile, line, ','))
    {
      try
      {
        tileNumber = std::stoi(line) - 1;
        tileMatrix.push_back(tileNumber);
      }
      catch (const std::invalid_argument &ia)
      {
        continue;
      }
    }
  }
  else
  {
    std::cout << "TileMap::Load: tileMapFile is not open" << std::endl;
    exit(1);
  }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
  this->tileSet = tileSet;
}

int *TileMap::At(int x, int y, int z)
{
  int *tileNumber = new int;
  *tileNumber = tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
  return tileNumber;
}

void TileMap::Render()
{
  for (int i = 0; i < mapDepth; i++)
  {
    RenderLayer(i);
  }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
  for (int i = 0; i < mapHeight; i++)
  {
    for (int j = 0; j < mapWidth; j++)
    {
      tileSet->RenderTile(*At(j, i, layer), j * tileSet->GetTileWidth() - cameraX, i * tileSet->GetTileHeight() - cameraY);
    }
  }
}

int TileMap::GetWidth()
{
  return mapWidth;
}

int TileMap::GetHeight()
{
  return mapHeight;
}

int TileMap::GetDepth()
{
  return mapDepth;
}

bool TileMap::Is(std::string type)
{
  return type == "TileMap";
}

void TileMap::Update(float dt)
{
}