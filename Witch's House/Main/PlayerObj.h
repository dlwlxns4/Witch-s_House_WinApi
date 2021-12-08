#pragma once
#include "GameObject.h"
#include "Config.h"
#include "PhysicsManager.h"

enum class Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
enum class PlayerActionState { None = 0, Move = 1, Run = 2, Chat = 3, Die = 4 };

class Image;
class PlayerObj : public GameObject
{
private:
	//referenceID
	int referenceID = 0;

	float tilePosX = 0;
	float tilePosY = 0;

	Direction direction = {};
	PlayerActionState state = {};

	int moveDelay = 0;
	int moveDistance = 0;
	int walkImage = 0;
	bool isRightFoot = false;


	//레이캐스트
	pair<int, int> rayCast{ 0,0 };
	int pastPosX = 0;
	int pastPosY = 0;

	//할 일 레이캐스트 갱신
public:
	PlayerObj() = default;
	virtual ~PlayerObj() = default;

	virtual HRESULT Init();
	HRESULT Init(int posX, int posY);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Move();
	void MoveHelper();
	void Action();
	void SetTilePos(int posX, int posY)
	{
		//위치
		tilePosX = (float)posX; tilePosY = (float)posY;
		pastPosX = posX, pastPosY = posY;

		//콜라이더
		SetRect(&(shape),
			posX * TILE_SIZE,
			posY * TILE_SIZE,
			(posX + 1) * TILE_SIZE,
			(posY + 1) * TILE_SIZE
		);

		PhysicsManager::GetSingleton()->AddCollider(&(shape), posX, posY);
	}
	void ReposRect()
	{
		SetRect(&(shape),
			(int)tilePosX * TILE_SIZE,
			(int)tilePosY * TILE_SIZE,
			(int)(tilePosX + 1) * TILE_SIZE,
			(int)(tilePosY + 1) * TILE_SIZE
		);
	}
	void CameraMove();
	void MoveInit();

	virtual void Write(ostream& os) const override
	{

		GameObject::Write(os);
		os << referenceID << endl;
		os << tilePosX << endl;
		os << tilePosY << endl;
		os << (int)direction << endl;
		os << (int)state << endl;
		os << moveDelay << endl;
		os << moveDistance << endl;
		os << walkImage << endl;
		os << isRightFoot << endl;
		os << rayCast.first << endl;
		os << rayCast.second << endl;
		os << pastPosX << endl;
		os << pastPosY << endl;
	}
};

