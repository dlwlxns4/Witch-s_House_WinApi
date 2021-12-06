#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class InventoryInterface : public GameObject
{
private:
	Image* itemInfoPanel;

	Image* inventoryPaenl;

	Image* opacityPanel;


	BLENDFUNCTION ftn = {};

public:
	InventoryInterface() = default;
	virtual ~InventoryInterface() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

