#include "UserInterface.h"
#include "Image.h"

#define CHAT_UI_POS_Y 11

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
	ftn.SourceConstantAlpha = 70;

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
		VARIABLE_PITCH | FF_ROMAN, TEXT("ÈÞ¸Õ³ª¹«")
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
		TILE_SIZE * CHAT_UI_POS_Y - opacityPaenl->GetHeight()/2,
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
		TextOut(hdc, 30, TILE_SIZE*CHAT_UI_POS_Y-40, TEXT(chat).c_str(), (int)chat.size());
		SetTextColor(hdc, RGB(0, 0, 0));
	}

	//----------------------------------------------------------------------------------

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void UserInterface::Release()
{
}
