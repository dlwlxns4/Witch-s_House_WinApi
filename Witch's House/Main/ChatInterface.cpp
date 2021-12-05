#include "ChatInterface.h"
#include "Image.h"

#define CHAT_UI_POS_Y 11

using namespace std;

HRESULT ChatInterface::Init()
{

	//ChatUI
	Mat callSize = OpencvHelper::ReadImage("Image/UI/ChatUI.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/ChatUI.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	chatUI = ImageManager::GetSingleton()->FindImage("Image/UI/ChatUI.bmp");

	//OpaictyPaenl
	callSize = OpencvHelper::ReadImage("Image/UI/OpacityPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/OpacityPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	opacityPaenl = ImageManager::GetSingleton()->FindImage("Image/UI/OpacityPanel.bmp");

	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 100;

	return S_OK;
}

void ChatInterface::Update()
{
	if (isTalking && slatePos<= opacityPaenl->GetHeight()/2)
	{
		slatePos+=8;
	}
	else if (isTalking == false && slatePos >= 0)
	{
		slatePos -= 8;
	}
}

void ChatInterface::Render(HDC hdc)
{

	//ChatUi ---------------------------------------------------------------------------
	if (isTalking)
	{
		chatUI->Render(hdc,
			0,
			TILE_SIZE * CHAT_UI_POS_Y-slatePos,
			chatUI->GetWidth(),
			slatePos,
			0,
			0,
			chatUI->GetWidth(),
			chatUI->GetHeight()/2
		);

		chatUI->Render(hdc,
			0,
			TILE_SIZE * CHAT_UI_POS_Y,
			chatUI->GetWidth(),
			slatePos,
			0,
			chatUI->GetHeight()-slatePos,
			chatUI->GetWidth(),
			slatePos
		);
		

		opacityPaenl->Render(hdc,
			8,
			TILE_SIZE * CHAT_UI_POS_Y ,
			0,
			0,
			opacityPaenl->GetWidth(),
			slatePos-8,
			opacityPaenl->GetWidth(),
			opacityPaenl->GetHeight(),
			ftn
		);
		opacityPaenl->Render(hdc,
			8,
			TILE_SIZE * CHAT_UI_POS_Y-slatePos+8,
			0,
			0,
			opacityPaenl->GetWidth(),
			slatePos-8,
			opacityPaenl->GetWidth(),
			opacityPaenl->GetHeight(),
			ftn
		);


		if (!chat.empty())
		{
			SetTextColor(hdc, RGB(255, 255, 255));

			if (chat != chatEffet)
			{
				chatEffet += chat[index++];
				cout << chatEffet << endl;
			}
		}

		TextOut(hdc, 30, TILE_SIZE * CHAT_UI_POS_Y - 40, TEXT(chatEffet).c_str(), (int)chatEffet.size());
	}
	SetTextColor(hdc, RGB(0, 0, 0));
	//----------------------------------------------------------------------------------

}

void ChatInterface::Release()
{
}
