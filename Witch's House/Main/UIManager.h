#pragma once

#include "Config.h"
#include "Singleton.h"

class GameObject;
class UserInfoInterface;
class ChatInterface;
class InventoryInterface;
class SaveLoadInterface;
class UIManager : public Singleton<UIManager>
{
private:
	UserInfoInterface* userInfoInterface;
	ChatInterface* chatInterface;
	InventoryInterface* inventoryInterface;
	SaveLoadInterface* saveLoadInterface;


	//------------------print
	bool isShowInventory = false;
	bool isShowUserInfo = false;
	bool isShowSaveLoad = false;
public:
	void Init();
	GameObject* GetUserInfoInterface();
	GameObject* GetChatInterface();
	GameObject* GetInventoryInterface();
	GameObject* GetSaveLoadInterface();

	void SetIsShowInventory(bool isShow) { isShowInventory = isShow; }
	bool GetIsShowInventory() { return isShowInventory; }
	void SetIsShowUserInfo(bool isShow) { isShowUserInfo = isShow; }
	bool GetIsShowUserInfo() { return isShowUserInfo; }
	void SetIsShowSaveLoad(bool isShow) { isShowSaveLoad = isShow; }
	bool GetIsShowSaveLoad() { return isShowSaveLoad; }
};
