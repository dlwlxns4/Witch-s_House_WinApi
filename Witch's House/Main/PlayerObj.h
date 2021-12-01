#pragma once
#include "GameObject.h"
#include "Config.h"

enum class Direction{Down=0, Left=1, Right=2, Up=3};
enum class PlayerState{None=0, Move=1, Run=2, Chat=3, Die=4};

class Image;
class PlayerObj : public GameObject
{
private:
	//referenceID
	int referenceID=0;

	float tilePosX = 0;
	float tilePosY = 0;

	Direction direction;
	PlayerState state;

	int moveDelay = 0;
	int moveDistance = 0;
	int walkImage = 0;
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

