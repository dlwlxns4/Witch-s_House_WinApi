#include "GameObject.h"
#include "Config.h"
//
//enum class Terrain { Earth, Wall, Water, Grass, BreakableWall, End };
//enum class TileType { Walkable, NoneWalkable };

#pragma once
class TileObj : public GameObject
{
private:

	TileType tileType;
	RECT rc;
	//image
	// sample tile의 아이디 (프레임 X, 프레임 Y)
	int frameX, frameY;
	int mapIndex;
	//RECT collider;		// Trigger Collider

public:
	TileObj() = default;
	virtual ~TileObj() = default;

	void SetPrintPos(RECT rc) { this->rc = rc;}
	void SetMapIndex(int mapIndex) { this->mapIndex = mapIndex; }
	void SetFramePos(int frameX, int frameY) { this->frameX = frameX; this->frameY = frameY; }
	void SetTileType(TileType tileType) { this->tileType = tileType; }
};

