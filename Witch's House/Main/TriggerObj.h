#include "Config.h"
#include "GameObject.h"
#include "PhysicsManager.h"

#pragma once
class TriggerObj : public GameObject
{


	TILE_INFO tile = {};
	int referenceID = 0;

public:
	TriggerObj() = default;
	virtual ~TriggerObj() = default;

	virtual HRESULT Init();
	virtual void Render(HDC hdc);
	virtual void Update();
	void SetTile(int posX, int posY, int frameX, int frameY, int mapIndex)
	{
		SetRect(&(tile.rc),
			posX * TILE_SIZE,
			posY * TILE_SIZE,
			posX * TILE_SIZE + TILE_SIZE,
			posY * TILE_SIZE + TILE_SIZE
		);
		tile.frameX = frameX;
		tile.frameY = frameY;
		tile.mapIndex = mapIndex;

		PhysicsManager::GetSingleton()->AddCollider(&(tile.rc), posX, posY);
		PhysicsManager::GetSingleton()->SetOwner(this, posX, posY);
	}
	bool ComparePos(int mousePosX, int mousePosY)
	{
		if (mousePosX * TILE_SIZE == tile.rc.left && mousePosY * TILE_SIZE == tile.rc.top)
		{
			return true;
		}
		return false;
	}

	void addReferenceID_1() { referenceID += 1; }
	void addReferenceID_10() { referenceID += 10; }
	void addReferenceID_100() { referenceID += 100; }
	void addReferenceID_1000() { referenceID += 1000; }

	int GetReferenceID() { return referenceID; }
};

