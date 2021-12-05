#pragma once


#include "Config.h"
#include "Singleton.h"

class GameObject;
class UserInfoInterface;
class UIManager : public Singleton<UIManager>
{
private:
	UserInfoInterface* userInfoInterface;

public:
	void Init();
	GameObject* GetUserInfoInterface();
};
