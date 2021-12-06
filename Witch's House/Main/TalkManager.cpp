#include "TalkManager.h"
#include "ReferenceId.h"
#include "ChatInterface.h"

void TalkManager::Init()
{
	talkData.emplace(TALK_LOG_ID, vector<string>{"썩은 통나무가 벌레의 집이 되어있다."});
	talkData.emplace(10, vector<string>{"."});
}

void TalkManager::FindChat(int referenceId)
{
	auto vecChat = talkData.find(referenceId);

	if (vecChat != talkData.end())
	{
		for (auto str : vecChat->second)
		{
			
			((ChatInterface*)UIManager::GetSingleton()->GetChatInterface())->SetChat(str);
			((ChatInterface*)UIManager::GetSingleton()->GetChatInterface())->SetIsTalking();

		}
	}
	else
	{
		cout << "몰?루" << endl;
	}
}


