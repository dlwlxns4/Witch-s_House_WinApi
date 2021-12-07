#include "GameObject.h"
#include "GameEntity.h"
#include "Config.h"

#pragma once
class Layer : public GameObject
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

	virtual void Write(ostream& os) const override
	{

		GameObject::Write(os);

		for (size_t i = 0; i < vecGameObject.size(); ++i)
		{
			vecGameObject[i]->Write(os);
		}
	}
};

