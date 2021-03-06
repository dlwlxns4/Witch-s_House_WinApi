#include "ParallaxObj.h"
#include "ImageHelper.h"
#include "Image.h"

HRESULT ParallaxObj::Init()
{
	return S_OK;
}

HRESULT ParallaxObj::Init(const char* filePath)
{
	Mat parallaxImage = OpencvHelper::ReadImage(filePath, 1);
	ImageManager::GetSingleton()->AddImage(filePath, TILE_SIZE * (TILE_COUNT_X) * 2, TILE_SIZE * (TILE_COUNT_Y) * 2, 1, 1, true, RGB(255, 0, 255));
	this->img = ImageManager::GetSingleton()->FindImage(filePath);
	this->filePath = filePath;

	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 50;

	return S_OK;
}

void ParallaxObj::Update()
{
	renderDelayTime++;
	if (renderDelayTime >= 2)
	{
		renderDelayTime = 0;
		renderPosX++;
		renderPosY++;

		//???ѷ???
		if (renderPosX == TILE_SIZE * (TILE_COUNT_X))
			renderPosX = 0;
		if (renderPosY == TILE_SIZE * (TILE_COUNT_Y))
			renderPosY = 0;
	}
}

void ParallaxObj::Render(HDC hdc)
{
	if (this->img != nullptr)
	{
		this->img->Render(hdc
			, 0
			, 0
			, renderPosX
			, renderPosY
			, img->GetWidth() / 2
			, img->GetHeight() / 2
			, TILE_SIZE * TILE_COUNT_X
			, TILE_SIZE * TILE_COUNT_Y
			, ftn
		);
		this->img->Render(hdc
			, 0
			, 0
			, renderPosX
			, 0
			, img->GetWidth()/2
			, img->GetHeight()/2
			, TILE_SIZE * TILE_COUNT_X
			, TILE_SIZE * TILE_COUNT_Y
			, ftn
		);
	}
}

void ParallaxObj::Release()
{
}

void ParallaxObj::SetImage()
{
	Mat parallaxImage = OpencvHelper::ReadImage(filePath, 1);
	ImageManager::GetSingleton()->AddImage(this->filePath.c_str(), TILE_SIZE * (TILE_COUNT_X) * 2, TILE_SIZE * (TILE_COUNT_Y) * 2, 1, 1, true, RGB(255, 0, 255));
	this->img = ImageManager::GetSingleton()->FindImage(filePath.c_str());
}
