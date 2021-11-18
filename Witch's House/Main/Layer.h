#include "GameObject.h"
#include "GameEntity.h"
#include "Config.h"

#pragma once
class Layer : public GameEntity
{
private:
	vector<GameObject*> gameObject;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

