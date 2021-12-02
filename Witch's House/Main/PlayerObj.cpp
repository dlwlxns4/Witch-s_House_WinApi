#include "PlayerObj.h"
#include "Image.h"
#include "ImageHelper.h"
#include "Camera.h"
#include "TriggerObj.h"

HRESULT PlayerObj::Init()
{
	return E_NOTIMPL;
}

HRESULT PlayerObj::Init(int posX, int posY)
{
	Mat charImg = imread("Image/Character/$vivi.bmp");
	this->img = ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp", charImg.cols, charImg.rows, charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));
	tilePosX = (float)posX;
	tilePosY = (float)posY;

	direction = Direction::Down;
	state = PlayerState::None;

	return S_OK;
}

void PlayerObj::Update()
{
	Move();
	Action();
}

void PlayerObj::Render(HDC hdc)
{
	if (this->img != nullptr)
	{

		this->img->Render(hdc
			, (int)(TILE_SIZE * (tilePosX + 1) - PLAYER_SIZE_X / 2 - (int)TILE_SIZE * g_cameraPosX)
			, (int)(TILE_SIZE * (tilePosY + 1) - PLAYER_SIZE_Y / 2 - (int)TILE_SIZE * g_cameraPosY)
			, walkImage
			, int(direction)
		);
	}
}

void PlayerObj::Release()
{
}

void PlayerObj::Move()
{

	if (state == PlayerState::None)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			state = PlayerState::Move;
			direction = Direction::Left;
			rayCast.first = (int)tilePosX - 1;
			rayCast.second = (int)tilePosY;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			state = PlayerState::Move;
			direction = Direction::Right;
			rayCast.first = (int)tilePosX + 1;
			rayCast.second = (int)tilePosY;
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			state = PlayerState::Move;
			direction = Direction::Up;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY - 1;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			state = PlayerState::Move;
			direction = Direction::Down;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY + 1;
		}

	}


	//충돌 안했을 때만 이동
	if (PhysicsManager::GetSingleton()->CheckCollider(rayCast.first, rayCast.second) == false)
	{
		if (state == PlayerState::Move)
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
		state = PlayerState::None;
	}
}

void PlayerObj::MoveHelper()
{
	switch (direction)
	{
	case Direction::Left:
		moveDistance += 4;
		tilePosX -= 0.125;
		if (g_cameraPosX > 0)
		{
			g_cameraPosX -= 0.125;
		}
		if (moveDistance == TILE_SIZE / 2)
		{
			isRightFoot = isRightFoot == true ? false : true;

			walkImage = isRightFoot == true ? 2 : 1;
		}
		if (moveDistance >= TILE_SIZE)
		{
			walkImage = 0;
			moveDistance = 0;
			state = PlayerState::None;
			ReposRect();
			PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
			PhysicsManager::GetSingleton()->AddCollider(&shape, (int)tilePosX, (int)tilePosY);
			pastPosX = (int)tilePosX;
			pastPosY = (int)tilePosY;
		}
		break;
	case Direction::Right:
		moveDistance += 4;
		tilePosX += 0.125;

		if (tilePosX > 8)
		{
			g_cameraPosX += 0.125;
		}
		if (moveDistance == TILE_SIZE / 2)
		{
			isRightFoot = isRightFoot == true ? false : true;

			walkImage = isRightFoot == true ? 2 : 1;
		}
		if (moveDistance >= TILE_SIZE)
		{
			walkImage = 0;
			moveDistance = 0;
			state = PlayerState::None;
			ReposRect();
			PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
			PhysicsManager::GetSingleton()->AddCollider(&shape, (int)tilePosX, (int)tilePosY);
			pastPosX = (int)tilePosX;
			pastPosY = (int)tilePosY;
		}
		break;
	case Direction::Up:
		moveDistance += 4;
		tilePosY -= 0.125;

		if (g_cameraPosY > 0)
		{
			g_cameraPosY -= 0.125;
		}
		if (moveDistance == TILE_SIZE / 2)
		{
			isRightFoot = isRightFoot == true ? false : true;

			walkImage = isRightFoot == true ? 2 : 1;
		}
		if (moveDistance >= TILE_SIZE)
		{
			walkImage = 0;
			moveDistance = 0;
			state = PlayerState::None;
			ReposRect();
			PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
			PhysicsManager::GetSingleton()->AddCollider(&shape, (int)tilePosX, (int)tilePosY);
			pastPosX = (int)tilePosX;
			pastPosY = (int)tilePosY;
		}
		break;
	case Direction::Down:
		moveDistance += 4;
		tilePosY += 0.125;
		if (tilePosY > 6)
		{
			g_cameraPosY += 0.125;
		}
		if (moveDistance == TILE_SIZE / 2)
		{
			isRightFoot = isRightFoot == true ? false : true;

			walkImage = isRightFoot == true ? 2 : 1;
		}
		if (moveDistance >= TILE_SIZE)
		{
			walkImage = 0;
			moveDistance = 0;
			state = PlayerState::None;
			ReposRect();
			PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
			PhysicsManager::GetSingleton()->AddCollider(&shape, (int)tilePosX, (int)tilePosY);
			pastPosX = (int)tilePosX;
			pastPosY = (int)tilePosY;
		}
		break;
	}
}

void PlayerObj::Action()
{

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LSHIFT))
	{
		GameObject* trigger = PhysicsManager::GetSingleton()->GetOwner(rayCast.first, rayCast.second);
		if (trigger != nullptr)
		{
			cout << ((TriggerObj*)trigger)->GetReferenceID() << endl;
			TalkManager::GetSingleton()->FindChat(((TriggerObj*)trigger)->GetReferenceID());
		}
	}
}

void PlayerObj::CameraMove()
{
	//if (g_cameraPosX < 0)
	//	g_cameraPosX-=0.125;
	//else if (g_cameraPosY < 0)
	//	g_cameraPosY -= 0.125;
}
