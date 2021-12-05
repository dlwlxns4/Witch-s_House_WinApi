#include "UserInfoInterface.h"
#include "Image.h"
#include "ImageHelper.h"

#define LEFT_PANEL_START_POSY 9
#define RIGHT_PANEL_START_POSX 5
#define RIGHT_PANEL_START_POSY 8
#define PORTRAIT_START_POSX 5
#define PORTRAIT_START_POSY 9

#define OPACITY_INTERVAL 6

#define STR_INVENTORY_POSY 324
#define STR_LOAD_POSY 356

#define STR_NAME_POSX 280
#define STR_NAME_POSY 322  


#define STR_AGE_POSX 280
#define STR_AGE_13_POSX 324
#define STR_AGE_POSY 358	

#define STR_HEALTH_POSX 380
#define STR_HEALTH_POSY 346  
#define HELTHBAR_POSY 370

#define STR_HP_POSX 424
#define STR_HP_POSY 346

#define PORTRAIT_SIZE 96

HRESULT UserInfoInterface::Init()
{
	Mat callSize = OpencvHelper::ReadImage("Image/UI/InfoUI_1.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/InfoUI_1.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	leftPanel = ImageManager::GetSingleton()->FindImage("Image/UI/InfoUI_1.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/InfoUI_2.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/InfoUI_2.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	rightPanel = ImageManager::GetSingleton()->FindImage("Image/UI/InfoUI_2.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/viviface.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/viviface.bmp", callSize.cols, callSize.rows, callSize.cols / PORTRAIT_SIZE, callSize.rows / PORTRAIT_SIZE, true, RGB(255, 0, 255));
	portrait = ImageManager::GetSingleton()->FindImage("Image/UI/viviface.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/OpacityPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/OpacityPanel.bmp", callSize.cols, callSize.rows, callSize.cols / PORTRAIT_SIZE, callSize.rows / PORTRAIT_SIZE, true, RGB(255, 0, 255));
	opacityPanel = ImageManager::GetSingleton()->FindImage("Image/UI/OpacityPanel.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/HealthBar.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/HealthBar.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	healthBar = ImageManager::GetSingleton()->FindImage("Image/UI/HealthBar.bmp");


	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 0;

	return S_OK;
}

void UserInfoInterface::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_CONTROL))
	{
		isShow = isShow == true ? false : true;
		ftn.SourceConstantAlpha = 0;
	}

	if (isShow && ftn.SourceConstantAlpha < 100)
	{
		ftn.SourceConstantAlpha += 10;
	}
}

void UserInfoInterface::Render(HDC hdc)
{
	if (isShow)
	{
		ShowInfoPanel(hdc);
	}

}

void UserInfoInterface::Release()
{
}

void UserInfoInterface::ShowInfoPanel(HDC hdc)
{
	opacityPanel->Render(hdc
		, 0
		, 0
		, 0
		, 0
		, TILE_SIZE * TILE_COUNT_X
		, TILE_SIZE * TILE_COUNT_Y
		, 10
		, 10
		, ftn
	);
	leftPanel->Render(hdc
		, 0
		, TILE_SIZE * LEFT_PANEL_START_POSY
		, leftPanel->GetWidth()
		, leftPanel->GetHeight()
		, 0
		, 0
		, leftPanel->GetWidth()
		, leftPanel->GetHeight()
	);
	opacityPanel->Render(hdc
		, 24
		, TILE_SIZE * LEFT_PANEL_START_POSY + 24
		, 0
		, 0
		, leftPanel->GetWidth() - 48
		, leftPanel->GetHeight() - 48
		, 10
		, 10
		, ftn
	);
	rightPanel->Render(hdc
		, TILE_SIZE * RIGHT_PANEL_START_POSX + 4
		, TILE_SIZE * LEFT_PANEL_START_POSY
		, rightPanel->GetWidth()
		, rightPanel->GetHeight()
		, 0
		, 0
		, rightPanel->GetWidth()
		, rightPanel->GetHeight()
	);
	opacityPanel->Render(hdc
		, TILE_SIZE * RIGHT_PANEL_START_POSX + 4
		, TILE_SIZE * LEFT_PANEL_START_POSY + 8
		, 0
		, 0
		, rightPanel->GetWidth() - 32 - 6
		, rightPanel->GetHeight() - 16
		, 10
		, 10
		, ftn
	);
	portrait->Render(hdc
		, TILE_SIZE * PORTRAIT_START_POSX + portrait->GetFrameWidth() / 2 + TILE_SIZE / 2
		, TILE_SIZE * PORTRAIT_START_POSY + portrait->GetFrameHeight() / 2 + TILE_SIZE / 2
		, 0
		, 0
	);

	healthBar->Render(hdc
		, STR_HEALTH_POSX
		, HELTHBAR_POSY
		, healthBar->GetWidth()
		, healthBar->GetHeight()
		, 0
		, 0
		, healthBar->GetWidth()
		, healthBar->GetHeight()
	);

	SetTextColor(hdc, RGB(255, 255, 255));
	string output = "소지품";
	TextOut(hdc, TILE_SIZE, STR_INVENTORY_POSY, output.c_str(), (int)output.size());
	output = "불러오기";
	TextOut(hdc, TILE_SIZE, STR_LOAD_POSY, output.c_str(), (int)output.size());
	output = name;
	TextOut(hdc, STR_NAME_POSX, STR_NAME_POSY, output.c_str(), (int)output.size());
	output = "13";
	TextOut(hdc, STR_AGE_13_POSX, STR_AGE_POSY, output.c_str(), (int)output.size());
	output = "10/   10";
	TextOut(hdc, STR_HP_POSX, STR_HP_POSY, output.c_str(), (int)output.size());


	SetTextColor(hdc, RGB(132, 172, 255));
	output = "나이";
	TextOut(hdc, STR_AGE_POSX, STR_AGE_POSY, output.c_str(), (int)output.size());
	output = "체력";
	TextOut(hdc, STR_HEALTH_POSX, STR_HEALTH_POSY, output.c_str(), (int)output.size());

	SetTextColor(hdc, RGB(0, 0, 0));

}
