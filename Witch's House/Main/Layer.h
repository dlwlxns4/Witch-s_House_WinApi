#pragma once

#include "GameEntity.h"
#include "Config.h"

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

	friend ostream& operator<<(ostream& os, const Layer& layer);
	friend istream& operator>>(istream& is, const Layer& layer);
};

ostream& operator<<(ostream& os, const Layer& layer);

istream& operator>>(istream& is, const Layer& layer);