#pragma once

#include "Config.h"
#include <unordered_map>
#include "Singleton.h"

class UserInterface;
class TalkManager : public Singleton<TalkManager>
{

private:
	unordered_map<int, vector<string>> talkData = {};
	string* uiChatString = nullptr;

	UserInterface* userInterface;

public:
	TalkManager() = default;
	virtual ~TalkManager() = default;

	void Init();
	void FindChat(int referenceId);
	void SetUI(UserInterface* UI);
	void SetChat(string chat);
};

