#include "Layer.h"
#include "GameObject.h"
#include "AllTypeObj.h"
#include "Tilemap.h"

HRESULT Layer::Init()
{
	return S_OK;
}

void Layer::Update()
{
	for (auto iter = vecGameObject.begin(); iter != vecGameObject.end(); ++iter)
	{
		(*iter)->Update();
	}
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


ostream& operator<<(ostream& os, const Layer& layer)
{
	for (size_t i = 0; i < layer.vecGameObject.size(); ++i)
	{
		os << *(layer.vecGameObject[i]) << endl;
	}

	return os;
}

istream& operator>>(istream& is, const Layer& layer)
{
	int tileType;
	is >> tileType;
	int currObjectIndeex = 0;

	if (tileType == 0)
	{
		TileObj* tileObject = new TileObj;
		tileObject->Init();
		vecTileObj.push_back(tileObject);
		vecLayer[vecLayer.size() - 1]->PushGameObject(vecTileObj[vecTileObj.size() - 1]);
	}

	is >> *(layer.vecGameObject[currObjectIndeex++]);
	return is;
}

