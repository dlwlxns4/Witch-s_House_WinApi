#include "PlayerObj.h"
#include "Image.h"
#include "ImageHelper.h"
#include "Camera.h"

HRESULT PlayerObj::Init()
{
	return E_NOTIMPL;
}

HRESULT PlayerObj::Init(int posX, int posY)
{
	Mat charImg = imread("Image/Character/$vivi.bmp");
	this->img = ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp", charImg.cols, charImg.rows, charImg.cols / PLAYER_SIZE_X, charImg.rows / PLAYER_SIZE_Y, true, RGB(255, 0, 255));
	tilePosX = posX;
	tilePosY = posY;

	direction = Direction::Down;
	state = PlayerState::None;

	return S_OK;
}

void PlayerObj::Update()
{
	Move();
}

void PlayerObj::Render(HDC hdc)
{
	if (this->img != nullptr)
	{

		this->img->Render(hdc
			, TILE_SIZE * tilePosX - PLAYER_SIZE_X / 2 - TILE_SIZE * g_cameraPosX
			, TILE_SIZE * tilePosY - PLAYER_SIZE_Y / 2 - TILE_SIZE * g_cameraPosY
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
	
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			state = PlayerState::Move;
			direction = Direction::Left;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			state = PlayerState::Move;
			direction = Direction::Right;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{
			state = PlayerState::Move;
			direction = Direction::Up;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			state = PlayerState::Move;
			direction = Direction::Down;
		}
	


	if (state == PlayerState::Move)
	{
		moveDelay++;
		if (moveDelay >= 2)
		{
			moveDelay = 0;
			if (direction == Direction::Left)
			{
				moveDistance += 4;
				tilePosX -= 0.125;
				if (moveDistance == TILE_SIZE / 2)
				{
					walkImage++;
				}
				if (moveDistance >= TILE_SIZE)
				{
					walkImage = 0;
					moveDistance = 0;
					state = PlayerState::None;
				}
			}
			else if (direction == Direction::Right)
			{
				moveDistance += 4;
				tilePosX += 0.125;
				if (moveDistance >= TILE_SIZE)
				{
					moveDistance = 0;
					state = PlayerState::None;
				}
			}
			else if (direction == Direction::Up)
			{
				moveDistance += 4;
				tilePosY -= 0.125;
				if (moveDistance >= TILE_SIZE)
				{
					moveDistance = 0;
					state = PlayerState::None;
				}
			}
			else if (direction == Direction::Down)
			{
				moveDistance += 4;
				tilePosY += 0.125;
				if (moveDistance >= TILE_SIZE)
				{
					moveDistance = 0;
					state = PlayerState::None;
				}
			}
		}
	}
}
