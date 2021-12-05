#pragma once

#include "Config.h"
#include <unordered_map>
#include "Singleton.h"

class ChatInterface;
class TalkManager : public Singleton<TalkManager>
{

private:
	unordered_map<int, vector<string>> talkData = {};
	string* uiChatString = nullptr;

	ChatInterface* userInterface;

public:
	TalkManager() = default;
	virtual ~TalkManager() = default;

	void Init();
	void FindChat(int referenceId);
	void SetUI(ChatInterface* UI);
	void SetChat(string chat);
};

