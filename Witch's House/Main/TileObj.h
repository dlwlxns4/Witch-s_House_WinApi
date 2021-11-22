#include "GameObject.h"
#include "Config.h"
#include <utility>
//
//enum class Terrain { Earth, Wall, Water, Grass, BreakableWall, End };
//enum class TileType { Walkable, NoneWalkable };

#pragma once
class TileObj : public GameObject
{
private:

	TILE_INFO tile[MAP_SIZE_X][MAP_SIZE_Y] = {};


public:
	TileObj() = default;
	virtual ~TileObj() = default;

	virtual HRESULT Init();
	virtual void Render(HDC hdc);
	virtual void Update();


	TILE_INFO GetTile(int posX, int posY) { return tile[posY][posX]; }
	void SetTile(int posX, int posY, int frameX, int frameY, int mapIndex) 
	{ 
		tile[posY][posX].frameX = frameX;
		tile[posY][posX].frameY = frameY;
		tile[posY][posX].mapIndex = mapIndex;
	}
	void SetTile(int posX, int posY, int frameX, int frameY)
	{
		tile[posY][posX].frameX = frameX;
		tile[posY][posX].frameY = frameY;
	}
};

