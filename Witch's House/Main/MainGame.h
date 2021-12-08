#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "GameObject.h"

// 우리가 구성할 게임 월드
class Image;
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer = nullptr;

	// 백버퍼
	Image* backBuffer = nullptr;

public:
	virtual ~MainGame() {}

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

