#pragma once
#include "GameObject.h"
#include "Config.h"

enum class Direction{Left=0, Right=1, Top=2, Bottom=3};

class Image;
class PlayerObj : public GameObject
{
private:
	//referenceID
	int referenceID=0;

	int tilePosX = 0;
	int tilePosY = 0;

	Direction direction;
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

