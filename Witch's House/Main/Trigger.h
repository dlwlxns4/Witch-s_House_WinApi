#include "Config.h"
#include "GameObject.h"

#pragma once
class Trigger : public GameObject
{
	TILE_INFO tile;
	int referenceID = 0;

public:
	Trigger() = default;
	virtual ~Trigger() = default;

	virtual HRESULT Init();
	virtual void Render(HDC hdc);
	virtual void Update();
	void SetTile(int posX, int posY, int frameX, int frameY, int mapIndex)
	{
		SetRect(&(tile.rc),
			posX * TILE_SIZE, posY * TILE_SIZE,
			posX * TILE_SIZE + TILE_SIZE, posY * TILE_SIZE + TILE_SIZE);
		tile.frameX = frameX;
		tile.frameY = frameY;
		tile.mapIndex = mapIndex;
	}
};

