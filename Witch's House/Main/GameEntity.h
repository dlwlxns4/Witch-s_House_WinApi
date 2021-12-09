#pragma once
#include <Windows.h>

class GameEntity
{
public:
	virtual ~GameEntity() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	//virtual void OnCollision(); // 충돌이 됐을 때 행동 정의부
};

