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
			if (uiChatString != nullptr)
			{
				*uiChatString = str;
			}

			userInterface->SetChat(str);
			userInterface->SetIsTalking();
		}
	}
	else
	{
		cout << "��?��" << endl;
	}
}

void TalkManager::SetUI(ChatInterface* UI)
{
	userInterface = UI;
}

void TalkManager::SetChat(string chat)
{
	userInterface->SetChat(chat);
}

