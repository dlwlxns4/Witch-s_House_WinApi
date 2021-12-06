#include "TalkManager.h"
#include "ReferenceId.h"
#include "ChatInterface.h"

void TalkManager::Init()
{
	talkData.emplace(TALK_LOG_ID, vector<string>{"���� �볪���� ������ ���� �Ǿ��ִ�."});
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
		cout << "��?��" << endl;
	}
}


