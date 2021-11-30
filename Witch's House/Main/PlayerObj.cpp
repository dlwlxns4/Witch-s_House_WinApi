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
	direction = Direction::Bottom;

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
			, 0
			, 0
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
		tilePosX--;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		tilePosX++;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		tilePosY--;
	}
	 if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		tilePosY++;
	}
}
