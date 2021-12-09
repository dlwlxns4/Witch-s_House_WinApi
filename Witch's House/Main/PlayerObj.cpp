#include "PlayerObj.h"
#include "Image.h"
#include "ImageHelper.h"
#include "Camera.h"
#include "TriggerObj.h"

#include "Input.h"

#include "PlayerMoveComponent.h"

#define LEFTFOOT 1
#define RIGHTFOOT 2
#define MOVE_AT_ONCE 4
#define HALFQUARTER 0.125

HRESULT PlayerObj::Init()
{



	Mat charImg = OpencvHelper::ReadImage("Image/Character/$vivi.bmp");
	ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp", charImg.cols, charImg.rows, charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));
	this->img = ImageManager::GetSingleton()->FindImage("Image/Character/$vivi.bmp");
	
	direction = Direction::Down;
	state = PlayerActionState::None;
	return S_OK;
}

HRESULT PlayerObj::Init(int posX, int posY)
{
	PlayerMoveComponent* playerMoveComponent = new PlayerMoveComponent(this, 1);
	playerMoveComponent->SetTilePos(posX, posY);

	Mat charImg = OpencvHelper::ReadImage("Image/Character/$vivi.bmp");
	ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp", charImg.cols, charImg.rows, charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));
	this->img = ImageManager::GetSingleton()->FindImage("Image/Character/$vivi.bmp");
	tilePosX = (float)posX;
	tilePosY = (float)posY;

	direction = Direction::Down;
	state = PlayerActionState::None;

	return S_OK;
}

void PlayerObj::Update()
{
	GameObject::Update();
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



void PlayerObj::Action()
{

	if (Input::GetButtonDown(VK_LSHIFT))
	{
		GameObject* trigger = PhysicsManager::GetSingleton()->GetOwner(rayCast.first, rayCast.second);
		if (trigger != nullptr && GameManager::GetSingleton()->GetPlayerState() != PlayerState::ShowUI)
		{
			cout << ((TriggerObj*)trigger)->GetReferenceID() << endl;
			TalkManager::GetSingleton()->FindChat(((TriggerObj*)trigger)->GetReferenceID());

			if (GameManager::GetSingleton()->GetPlayerState() == PlayerState::None)
			{
				GameManager::GetSingleton()->SetPlayerState(PlayerState::Chat);
			}
			else if (GameManager::GetSingleton()->GetPlayerState() == PlayerState::Chat)
			{
				GameManager::GetSingleton()->SetPlayerState(PlayerState::None);
			}
		}
	}
}

