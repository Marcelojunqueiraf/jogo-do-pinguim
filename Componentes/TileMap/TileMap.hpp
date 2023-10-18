#pragma once
#include <vector>
#include "../Component/Component.hpp"
#include "../../Utils/TileSet/TileSet.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Utils/Vec2/Vec2.hpp"

class TileSet;

class TileMap : public Component
{
private:
  std::vector<int> tileMatrix;
  TileSet *tileSet;
  int mapWidth;
  int mapHeight;
  int mapDepth;

public:
  TileMap(std::weak_ptr<GameObject> associated, std::string file, TileSet *tileSet);
  void Start();
  void Load(std::string file);
  void SetTileSet(TileSet *tileSet);
  int *At(int x, int y, int z = 0);
  void Render();
  void RenderLayer(int layer);
  int GetWidth();
  int GetHeight();
  int GetDepth();
  bool Is(std::string type);
  void Update(float dt);
};