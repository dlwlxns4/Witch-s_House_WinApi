
#include "UIManager.h"
#include "UserInfoInterface.h"
#include "GameObject.h"

void UIManager::Init()
{
	userInfoInterface = new UserInfoInterface;
	userInfoInterface->Init();
}

GameObject* UIManager::GetUserInfoInterface()
{
	return userInfoInterface;
}
