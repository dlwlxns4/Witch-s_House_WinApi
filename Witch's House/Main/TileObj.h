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


	virtual void Write(ostream& os) const override
	{
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			for (int j = 0; j < MAP_SIZE_Y; ++j)
			{
				os << tile[i][j].collider.left;
				os << tile[i][j].collider.top;
				os << tile[i][j].collider.right;
				os << tile[i][j].collider.bottom;

				os << tile[i][j].frameX;
				os << tile[i][j].frameY;
				os << tile[i][j].mapIndex;

				os << tile[i][j].rc.left;
				os << tile[i][j].rc.top;
				os << tile[i][j].rc.right;
				os << tile[i][j].rc.bottom;
			}
		}
	}

};

