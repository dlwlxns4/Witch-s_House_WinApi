#include "Layer.h"

HRESULT Layer::Init()
{
	return S_OK;
}

void Layer::Update()
{
}

void Layer::Render(HDC hdc)
{
	for (auto iter = vecGameObject.begin(); iter!= vecGameObject.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}
}

void Layer::Release()
{
	for (auto iter : vecGameObject)
	{
		SAFE_DELETE(iter);
	}
	
}

void Layer::PushGameObject(GameObject* gameObject)
{
	vecGameObject.push_back(gameObject);
}
