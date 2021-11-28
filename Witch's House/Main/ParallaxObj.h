#include "GameObject.h"

#pragma once
class ParallaxObj
{

public:
	virtual HRESULT Init();
	HRESULT Init(int posX, int posY);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

