#include "GameObject.h"
#include "Config.h"

#pragma once
class ParallaxObj : public GameObject
{
	BLENDFUNCTION ftn;


	int renderPosX = 0;
	int renderPosY = 0;
	int renderDelayTime = 0;

public:
	ParallaxObj() = default;
	virtual ~ParallaxObj() = default;

	virtual HRESULT Init();
	HRESULT Init(const char* filePath);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

