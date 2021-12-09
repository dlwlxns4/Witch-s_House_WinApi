#pragma once
#include "Config.h"
#include "GameObject.h"
#include "ImageHelper.h"

// ChatUI
class ChatInterface : public GameObject
{
private:
	Image* chatUI = nullptr;
	Image* userInfoUI = nullptr;

	Image* opacityPaenl = nullptr;
	BLENDFUNCTION ftn = {};

	string chat = {};
	string chatEffet = "";
	int chatEffetDelay = 0;
	int index = 0;


	bool isTalking = false;
	int slatePos = 0;
	int slateUnderPos = 0;


public:
	ChatInterface() = default;
	virtual ~ChatInterface() = default;
	
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ShowChatUI();
	void SetChat(string otherChat) { chatEffet.clear(); chat = otherChat; index = 0; slatePos = 0; }
	void SetIsTalking() { isTalking = isTalking == false ? true : false; }
};

