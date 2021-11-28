#include "PlayerObj.h"
#include "Image.h"
#include "ImageHelper.h"

HRESULT PlayerObj::Init()
{
	Mat charImg = imread("Image/Character/$vivi.bmp");
	this->img = ImageManager::GetSingleton()->AddImage("Image/Character/$vivi.bmp",charImg.cols,charImg.rows, charImg.cols/32, charImg.rows/48, true, RGB(255,0,255));

	return S_OK;
}

void PlayerObj::Update()
{
}

void PlayerObj::Render(HDC hdc)
{
	if (this->img != nullptr)
	{
		this->img->Render(hdc
		,16
		,24
		,0
		,0
		);

	}
}

void PlayerObj::Release()
{
}
