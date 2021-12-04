#pragma once
#include "Config.h"
#include "GameObject.h"
#include "ImageHelper.h"

class UserInterface : public GameObject
{
private:
	Image* chatUI = nullptr;
	Image* userInfoUI = nullptr;

	Image* opacityPaenl = nullptr;
	BLENDFUNCTION ftn = {};

	string chat = {};

public:
	UserInterface() = default;
	virtual ~UserInterface() = default;
	
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ShowChatUI();

};

