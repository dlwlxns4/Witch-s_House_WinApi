#pragma once
#include "Component.h"
#include <utility>

enum class Direction2 { Down = 0, Left = 1, Right = 2, Up = 3 };
enum class PlayerActionState2 { None = 0, Move = 1, Run = 2, Chat = 3, Die = 4 };

using namespace std;

class PlayerMoveComponent : public Component
{
private:
	//referenceID
	int referenceID = 0;

	float tilePosX = 0;
	float tilePosY = 0;

	Direction2 direction = {};
	PlayerActionState2 state = {};

	int moveDelay = 0;
	int moveDistance = 0;
	int walkImage = 0;
	bool isRightFoot = false;


	//레이캐스트
	pair<int, int> rayCast{ 0,0 };
	int pastPosX = 0;
	int pastPosY = 0;


public:
	using Component::Component;
	virtual ~PlayerMoveComponent() noexcept = default;

	virtual void Update() override;
	void Move();
	void MoveHelper();
	void SetTilePos(int posX, int posY);
	void ReposRect();
	void MoveInit();
};

