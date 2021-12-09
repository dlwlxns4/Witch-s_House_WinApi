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
	void SetTilePos(int posX, int posY);
	void SetTile(){	PhysicsManager::GetSingleton()->AddCollider(&(shape), tilePosX, tilePosY);}
	void ReposRect();
	void CameraMove();
	void MoveInit();

	virtual void Write(ostream& os) const override
	{
		os << 1 << "\t"; // tileType;

		GameObject::Write(os);

		os << referenceID << "\t";
		os << tilePosX << "\t";
		os << tilePosY << "\t";
		os << moveDelay << "\t";
		os << moveDistance << "\t";
		os << walkImage << "\t";
		os << isRightFoot << "\t";
		os << rayCast.first << "\t";
		os << rayCast.second << "\t";
		os << pastPosX << "\t";
		os << pastPosY << "\t";
	}

	virtual void Read(istream& is) override
	{
		GameObject::Read(is);
		is >> referenceID
			>> tilePosX
			>> tilePosY
			>> moveDelay
			>> moveDistance
			>> walkImage
			>> isRightFoot
			>> rayCast.first
			>> rayCast.second
			>> pastPosX
			>> pastPosY;
	}
};

