#include "UserInterface.h"
#include "Image.h"

#define CHAT_UI_POS_Y 11

using namespace std;

HRESULT UserInterface::Init()
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

void UserInterface::Update()
{

}

void UserInterface::Render(HDC hdc)
{
	HFONT hFont = CreateFont(
		20,
		0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("�޸ճ���")
	);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	//ChatUi ---------------------------------------------------------------------------
	chatUI->Render(hdc,
		chatUI->GetWidth() / 2,
		TILE_SIZE * CHAT_UI_POS_Y,
		0,
		0
	);
	opacityPaenl->Render(hdc,
		6,
		TILE_SIZE * CHAT_UI_POS_Y - opacityPaenl->GetHeight() / 2,
		0,
		0,
		opacityPaenl->GetWidth(),
		opacityPaenl->GetHeight(),
		opacityPaenl->GetWidth(),
		opacityPaenl->GetHeight(),
		ftn
	);

	if (!chat.empty())
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		if (chat != chatEffet)
		{
			chatEffet += chat[index++];
			cout << chatEffet << endl;
		}
	}

	TextOut(hdc, 30, TILE_SIZE * CHAT_UI_POS_Y - 40, TEXT(chatEffet).c_str(), (int)chatEffet.size());

	SetTextColor(hdc, RGB(0, 0, 0));
	//----------------------------------------------------------------------------------

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void UserInterface::Release()
{
}