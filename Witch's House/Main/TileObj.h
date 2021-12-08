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
		os << 0 << "\t"; // tileType;

		GameObject::Write(os);


		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			for (int j = 0; j < MAP_SIZE_Y; ++j)
			{
				os << tile[i][j].collider.left << "\t";
				os << tile[i][j].collider.top << "\t";
				os << tile[i][j].collider.right << "\t";
				os << tile[i][j].collider.bottom << "\t";

				os << tile[i][j].frameX << "\t";
				os << tile[i][j].frameY << "\t";
				os << tile[i][j].mapIndex << "\t";

				os << tile[i][j].rc.left << "\t";
				os << tile[i][j].rc.top << "\t";
				os << tile[i][j].rc.right << "\t";
				os << tile[i][j].rc.bottom << "\t";
			}
		}
		os << endl;
	}

	virtual void Read(istream& is) override
	{

		GameObject::Read(is);
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			for (int j = 0; j < MAP_SIZE_Y; ++j)
			{
				is >> tile[i][j].collider.left
					>> tile[i][j].collider.top
					>> tile[i][j].collider.right
					>> tile[i][j].collider.bottom

					>> tile[i][j].frameX
					>> tile[i][j].frameY
					>> tile[i][j].mapIndex

					>> tile[i][j].rc.left
					>> tile[i][j].rc.top
					>> tile[i][j].rc.right
					>> tile[i][j].rc.bottom;
			}
		}
	}

};

