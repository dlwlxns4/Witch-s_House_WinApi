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
		this->SetPos({ (float)posX, (float)posY });
		SetRect(&(tile.rc),
			(int)this->pos.x * TILE_SIZE,
			(int)this->pos.y * TILE_SIZE,
			(int)this->pos.x * TILE_SIZE + TILE_SIZE,
			(int)this->pos.y * TILE_SIZE + TILE_SIZE
		);
		tile.frameX = frameX;
		tile.frameY = frameY;
		tile.mapIndex = mapIndex;

		PhysicsManager::GetSingleton()->AddCollider(&(tile.rc), posX, posY);
		PhysicsManager::GetSingleton()->SetOwner(this, posX, posY);
	}
	void SetTile()
	{
		SetRect(&(tile.rc),
			(int)this->pos.x * TILE_SIZE,
			(int)this->pos.y * TILE_SIZE,
			(int)this->pos.x * TILE_SIZE + TILE_SIZE,
			(int)this->pos.y * TILE_SIZE + TILE_SIZE
		);

		PhysicsManager::GetSingleton()->AddCollider(&(tile.rc), this->pos.x, this->pos.y);
		PhysicsManager::GetSingleton()->SetOwner(this, this->pos.x, this->pos.y);
		
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

	virtual void Write(ostream& os) const override
	{
		os << 2 << "\t"; // tileType;

		GameObject::Write(os);

		os << tile.collider.left << "\t";
		os << tile.collider.top << "\t";
		os << tile.collider.right << "\t";
		os << tile.collider.bottom << "\t";


		os << tile.frameX << "\t";
		os << tile.frameY << "\t";
		os << tile.mapIndex << "\t";


		os << tile.rc.left << "\t";
		os << tile.rc.top << "\t";
		os << tile.rc.right << "\t";
		os << tile.rc.bottom << "\t";
	}

	virtual void Read(istream& is) override
	{
		GameObject::Read(is);

		is >> tile.collider.left
			>> tile.collider.top
			>> tile.collider.right
			>> tile.collider.bottom


			>> tile.frameX
			>> tile.frameY
			>> tile.mapIndex


			>> tile.rc.left
			>> tile.rc.top
			>> tile.rc.right
			>> tile.rc.bottom;
	}
};

