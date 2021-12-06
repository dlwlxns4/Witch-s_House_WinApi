
#include "UIManager.h"
#include "UserInfoInterface.h"
#include "GameObject.h"
#include "InventoryInterface.h"
#include "SaveLoadInterface.h"
#include "ChatInterface.h"

void UIManager::Init()
{
	chatInterface = new ChatInterface;
	chatInterface->Init();

	userInfoInterface = new UserInfoInterface;
	userInfoInterface->Init();

	inventoryInterface = new InventoryInterface;
	inventoryInterface->Init();

	saveLoadInterface = new SaveLoadInterface;
	saveLoadInterface->Init();
}

GameObject* UIManager::GetUserInfoInterface()
{
	return userInfoInterface;
}

GameObject* UIManager::GetChatInterface()
{
	return chatInterface;
}

GameObject* UIManager::GetInventoryInterface()
{
	return inventoryInterface;
}

GameObject* UIManager::GetSaveLoadInterface()
{
	return saveLoadInterface;
}
