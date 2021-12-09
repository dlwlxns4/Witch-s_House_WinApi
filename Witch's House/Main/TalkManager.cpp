#include "TalkManager.h"
#include "ReferenceId.h"
#include "ChatInterface.h"

void TalkManager::Init()
{
	//-----------------------나무-----------------------------------
	talkData.emplace(TALK_LOG_ID, vector<string>{"썩은 통나무가 벌레의 집이 되어있다."});
	talkData.emplace(TALK_WITHER_TREE_ID, vector<string>{"시들어버린 나무가 있다."});
	talkData.emplace(TALK_OVERGROUN_TREE_ID, vector<string>{"파릇파릇하게 우거진 나무가 있다."});


	//----------------------풀--------------------------------------
	talkData.emplace(TALK_ROUGH_GRASS_ID, vector<string>{"삐죽삐죽하게 억센 풀이 자라고 있다."});

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


