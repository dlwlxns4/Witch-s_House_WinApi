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
	for (auto iter = vecGameObject.begin(); iter != vecGameObject.end(); ++iter)
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
	int currObjectIndex = 0;
	int tileType=0;


	//현재 문제 -1들어가는거
	do
	{
	is >> tileType;

		switch (tileType)
		{
			case 0:
			{
				TileObj* tileObject = new TileObj;
				tileObject->Init();
				is >> *tileObject;
				vecTileObj.push_back(tileObject);
				vecLayer[vecLayer.size() - 1]->PushGameObject(vecTileObj[vecTileObj.size() - 1]);
				break;
			}
			case 1:
			{
				PlayerObj* playerObj = new PlayerObj;
				playerObj->Init();
				is >> *playerObj;
				vecLayer[vecLayer.size() - 1]->PushGameObject(playerObj);
				break;
			}
			case 2:
			{
				TriggerObj* triggerObj = new TriggerObj;
				triggerObj->Init();
				is >> *triggerObj;
				vecLayer[vecLayer.size() - 1]->PushGameObject(triggerObj);
				break;
			}
			case 3:
			{
				ParallaxObj* parallaxObj = new ParallaxObj;
				parallaxObj->Init();
				is >> *parallaxObj;
				vecLayer[vecLayer.size() - 1]->PushGameObject(parallaxObj);
				break;
			}
		}


	} while (tileType != -1);

	return is;
}

