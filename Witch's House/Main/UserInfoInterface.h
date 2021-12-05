#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class UserInfoInterface : public GameObject
{
private:
	Image* leftPanel = nullptr;

	Image* rightPanel = nullptr;

	Image* opacityPanel = nullptr;
	Image* portrait = nullptr;

	Image* healthBar = nullptr;

	bool isShow = false;

	string name = "��ö�";

	BLENDFUNCTION ftn = {};
public:
	UserInfoInterface() = default;
	virtual ~UserInfoInterface() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ShowInfoPanel(HDC hdc);

};

