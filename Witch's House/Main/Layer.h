#include "GameObject.h"
#include "GameEntity.h"
#include "Config.h"

#pragma once
class Layer : public GameEntity
{
private:
	vector<GameObject*> vecGameObject;

public:

	Layer() = default;
	virtual ~Layer() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void PushGameObject(GameObject* gameObject);
};

