#pragma once
#include "Config.h"
#include "GameObject.h"

class SaveLoadInterface : public GameObject
{
private:
	Image* infoPanel;

	Image* saveLoadPanel;

	Image* opacityPanel;

	Image* selectPaenl;

	int selectNum = 0;

	bool isTransparency = true;
	BLENDFUNCTION selectFtn = {};
	BLENDFUNCTION ftn = {};

public:
	SaveLoadInterface() = default;
	virtual ~SaveLoadInterface() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

