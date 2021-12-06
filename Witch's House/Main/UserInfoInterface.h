#pragma once
#include "Config.h"
#include "GameObject.h"

enum class SelectState { Inventory = 0, Load = 1 };

class Image;
class UserInfoInterface : public GameObject
{
private:
	Image* leftPanel = nullptr;

	Image* rightPanel = nullptr;

	Image* opacityPanel = nullptr;
	Image* portrait = nullptr;

	Image* healthBar = nullptr;

	//------------------------
	Image* selectPaenl = nullptr;
	bool isTransparency = true;

	//--------------------------

	string name = "ºñ¿Ã¶ó";

	BLENDFUNCTION ftn = {};
	BLENDFUNCTION selectFtn = {};

	SelectState selectState = SelectState::Inventory;

public:
	UserInfoInterface() = default;
	virtual ~UserInfoInterface() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ShowInfoPanel(HDC hdc);

};

