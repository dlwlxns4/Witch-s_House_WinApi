#include "ParallaxObj.h"
#include "ImageHelper.h"
#include "Image.h"

HRESULT ParallaxObj::Init()
{
	return E_NOTIMPL;
}

HRESULT ParallaxObj::Init(const char* filePath)
{
	Mat parallaxImage = OpencvHelper::ReadImage(filePath, 1);
	this->img = ImageManager::GetSingleton()->AddImage(filePath, TILE_SIZE * (TILE_COUNT_X)*2, TILE_SIZE * (TILE_COUNT_Y)*2, 1, 1, true, RGB(255, 0, 255));
	
	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 30;

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

		//���ѷ���
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
			, TILE_SIZE * (TILE_COUNT_X ) / 2
			, TILE_SIZE * (TILE_COUNT_Y ) / 2
			, renderPosX
			, renderPosY
			, ftn
		);
		this->img->Render(hdc
			, TILE_SIZE * (TILE_COUNT_X + 1) / 2
			, TILE_SIZE * (TILE_COUNT_Y + 1) / 2
			, renderPosX
			, 0
			, ftn
		);
	}
}

void ParallaxObj::Release()
{
}
