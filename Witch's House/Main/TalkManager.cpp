#include "TalkManager.h"
#include "ReferenceId.h"
#include "ChatInterface.h"

void TalkManager::Init()
{
	//-----------------------����-----------------------------------
	talkData.emplace(TALK_LOG_ID, vector<string>{"���� �볪���� ������ ���� �Ǿ��ִ�."});
	talkData.emplace(TALK_WITHER_TREE_ID, vector<string>{"�õ����� ������ �ִ�."});
	talkData.emplace(TALK_OVERGROUN_TREE_ID, vector<string>{"�ĸ��ĸ��ϰ� ����� ������ �ִ�."});


	//----------------------Ǯ--------------------------------------
	talkData.emplace(TALK_ROUGH_GRASS_ID, vector<string>{"���׻����ϰ� �＾ Ǯ�� �ڶ�� �ִ�."});

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
		cout << "��?��" << endl;
	}
}


