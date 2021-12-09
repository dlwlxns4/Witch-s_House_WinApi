#include "PlayerMoveComponent.h"
#include "Config.h"
#include "Input.h"
#include "Camera.h"
#include "GameObject.h"
#include "PhysicsManager.h"

#define LEFTFOOT 1
#define RIGHTFOOT 2
#define MOVE_AT_ONCE 4
#define HALFQUARTER 0.125


void PlayerMoveComponent::Update()
{
	Move();

}


void PlayerMoveComponent::Move()
{

	if (state == PlayerActionState2::None)
	{
		if (Input::GetButton(VK_LEFT))
		{
			state = PlayerActionState2::Move;
			direction = Direction2::Left;
			rayCast.first = (int)tilePosX - 1;
			rayCast.second = (int)tilePosY;
		}
		else if (Input::GetButton(VK_RIGHT))
		{
			state = PlayerActionState2::Move;
			direction = Direction2::Right;
			rayCast.first = (int)tilePosX + 1;
			rayCast.second = (int)tilePosY;
		}

		if (Input::GetButton(VK_UP))
		{
			state = PlayerActionState2::Move;
			direction = Direction2::Up;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY - 1;
		}
		if (Input::GetButton(VK_DOWN))
		{
			state = PlayerActionState2::Move;
			direction = Direction2::Down;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY + 1;
		}

	}


	//충돌 안했을 때만 이동
	if (PhysicsManager::GetSingleton()->CheckCollider(rayCast.first, rayCast.second) == false)
	{
		if (state == PlayerActionState2::Move)
		{
			moveDelay++;
			if (moveDelay >= 2)
			{
				moveDelay = 0;
				MoveHelper();
			}
		}
	}
	else
	{
		state = PlayerActionState2::None;
	}
}

void PlayerMoveComponent::MoveHelper()
{
	int dx[] = { 0,-1,1,0 };
	int dy[] = { 1,0,0,-1 };

	moveDistance += MOVE_AT_ONCE;
	tilePosX += HALFQUARTER * dx[(int)direction];
	tilePosY += HALFQUARTER * dy[(int)direction];

	//rayCast.first += dx[(int)direction];
	//rayCast.second += dy[(int)direction];

	//카메라 이동
	if (dx[(int)direction] == -1 && g_cameraPosX > 0)
	{
		g_cameraPosX -= HALFQUARTER;
	}
	else if (dx[(int)direction] == 1 && tilePosX > TILE_COUNT_X / 2)
	{
		g_cameraPosX += HALFQUARTER;
	}
	else if (dy[(int)direction] == -1 && g_cameraPosY > 0)
	{
		g_cameraPosY -= HALFQUARTER;
	}
	else if (dy[(int)direction] == 1 && tilePosY > TILE_COUNT_Y / 2)
	{
		g_cameraPosY += HALFQUARTER;
	}

	MoveInit();
}



void PlayerMoveComponent::SetTilePos(int posX, int posY)
{
	//위치
	tilePosX = (float)posX; tilePosY = (float)posY;
	pastPosX = posX, pastPosY = posY;

	//콜라이더
	RECT* rc = (_owner->GetShapeAddress());
	SetRect( rc,
		posX * TILE_SIZE,
		posY * TILE_SIZE,
		(posX + 1) * TILE_SIZE,
		(posY + 1) * TILE_SIZE
	);

	PhysicsManager::GetSingleton()->AddCollider(rc, posX, posY);
}

void PlayerMoveComponent::ReposRect()
{

	RECT* rc = (_owner->GetShapeAddress());
	SetRect(rc,
		(int)tilePosX * TILE_SIZE,
		(int)tilePosY * TILE_SIZE,
		(int)(tilePosX + 1) * TILE_SIZE,
		(int)(tilePosY + 1) * TILE_SIZE
	);
}



void PlayerMoveComponent::MoveInit()
{
	if (moveDistance == TILE_SIZE / 2)
	{
		isRightFoot = isRightFoot == true ? false : true;

		walkImage = isRightFoot == true ? LEFTFOOT : RIGHTFOOT;
	}

	if (moveDistance >= TILE_SIZE)
	{

		RECT* rc = (_owner->GetShapeAddress());
		walkImage = 0;
		moveDistance = 0;
		state = PlayerActionState2::None;
		ReposRect();
		PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
		PhysicsManager::GetSingleton()->AddCollider(rc, (int)tilePosX, (int)tilePosY);
		pastPosX = (int)tilePosX;
		pastPosY = (int)tilePosY;
	}
}
