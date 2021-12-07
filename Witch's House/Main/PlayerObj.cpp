#include "PlayerObj.h"
#include "Image.h"
#include "ImageHelper.h"
#include "Camera.h"
#include "TriggerObj.h"

#include "Input.h"

#define LEFTFOOT 1
#define RIGHTFOOT 2
#define MOVE_AT_ONCE 4
#define HALFQUARTER 0.125

HRESULT PlayerObj::Init()
{
	return E_NOTIMPL;
}

HRESULT PlayerObj::Init(int posX, int posY)
{
	Mat charImg = OpencvHelper::ReadImage("Image/Character/$vivi.bmp");
	this->img = ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp", charImg.cols, charImg.rows, charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));
	tilePosX = (float)posX;
	tilePosY = (float)posY;

	direction = Direction::Down;
	state = PlayerActionState::None;

	return S_OK;
}

void PlayerObj::Update()
{
	if (GameManager::GetSingleton()->GetPlayerState() == PlayerState::None)
	{
		Move();
	}
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

	if (state == PlayerActionState::None)
	{
		if (Input::GetButton(VK_LEFT))
		{
			state = PlayerActionState::Move;
			direction = Direction::Left;
			rayCast.first = (int)tilePosX - 1;
			rayCast.second = (int)tilePosY;
		}
		else if (Input::GetButton(VK_RIGHT))
		{
			state = PlayerActionState::Move;
			direction = Direction::Right;
			rayCast.first = (int)tilePosX + 1;
			rayCast.second = (int)tilePosY;
		}

		if (Input::GetButton(VK_UP))
		{
			state = PlayerActionState::Move;
			direction = Direction::Up;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY - 1;
		}
		if (Input::GetButton(VK_DOWN))
		{
			state = PlayerActionState::Move;
			direction = Direction::Down;
			rayCast.first = (int)tilePosX;
			rayCast.second = (int)tilePosY + 1;
		}

	}


	//충돌 안했을 때만 이동
	if (PhysicsManager::GetSingleton()->CheckCollider(rayCast.first, rayCast.second) == false)
	{
		if (state == PlayerActionState::Move)
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
		state = PlayerActionState::None;
	}
}

void PlayerObj::MoveHelper()
{
	int dx[] = { 0,-1,1,0 };
	int dy[] = { 1,0,0,-1 };

	moveDistance += MOVE_AT_ONCE;
	tilePosX += HALFQUARTER * dx[(int)direction];
	tilePosY += HALFQUARTER * dy[(int)direction];

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

void PlayerObj::Action()
{

	if (Input::GetButtonDown(VK_LSHIFT))
	{
		GameObject* trigger = PhysicsManager::GetSingleton()->GetOwner(rayCast.first, rayCast.second);
		if (trigger != nullptr)
		{
			cout << ((TriggerObj*)trigger)->GetReferenceID() << endl;
			TalkManager::GetSingleton()->FindChat(((TriggerObj*)trigger)->GetReferenceID());

			if (GameManager::GetSingleton()->GetPlayerState() == PlayerState::None)
			{
				GameManager::GetSingleton()->SetPlayerState(PlayerState::Chat);
			}
			else if (GameManager::GetSingleton()->GetPlayerState() == PlayerState::ShowUI)
			{
				GameManager::GetSingleton()->SetPlayerState(PlayerState::None);
			}
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

void PlayerObj::MoveInit()
{
	if (moveDistance == TILE_SIZE / 2)
	{
		isRightFoot = isRightFoot == true ? false : true;

		walkImage = isRightFoot == true ? LEFTFOOT : RIGHTFOOT;
	}

	if (moveDistance >= TILE_SIZE)
	{
		walkImage = 0;
		moveDistance = 0;
		state = PlayerActionState::None;
		ReposRect();
		PhysicsManager::GetSingleton()->SetColliderNullptr(pastPosX, pastPosY);
		PhysicsManager::GetSingleton()->AddCollider(&shape, (int)tilePosX, (int)tilePosY);
		pastPosX = (int)tilePosX;
		pastPosY = (int)tilePosY;
	}
}
