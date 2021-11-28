#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class PlayerObj : public GameObject
{
private:
	//referenceID
	int referenceID=0;

	int tilePosX = 0;
	int tilePosY = 0;
public:
	PlayerObj() = default;
	virtual ~PlayerObj() = default;

	virtual HRESULT Init();
	HRESULT Init(int posX, int posY);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Move();
	void SetTilePos(int posX, int posY) { tilePosX = posX; tilePosY = posY; }
};

