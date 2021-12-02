#include "TalkManager.h"

void TalkManager::Init()
{
	talkData.emplace(0, vector<string>{"썩은 통나무가 벌레의 집이 되어있다."});
}

void TalkManager::FindChat(int referenceId)
{
	auto vecChat = talkData.find(referenceId);

	if (vecChat != talkData.end())
	{
		cout << "@" << endl;
		for (auto str : vecChat->second)
		{
			cout << str << endl;
		}
	}
	else
	{
		cout << "몰?루" << endl;
	}
}
