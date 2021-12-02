#pragma once

#include "Config.h"
#include <unordered_map>
#include "Singleton.h"

class TalkManager : public Singleton<TalkManager>
{

private:
	unordered_map<int, vector<string>> talkData = {};


public:
	TalkManager() = default;
	virtual ~TalkManager() = default;

	void Init();
	void FindChat(int referenceId);
};

