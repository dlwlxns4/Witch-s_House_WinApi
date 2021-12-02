#include "TalkManager.h"

void TalkManager::Init()
{
	talkData.emplace(0, vector<string>{"���� �볪���� ������ ���� �Ǿ��ִ�."});
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
		cout << "��?��" << endl;
	}
}
