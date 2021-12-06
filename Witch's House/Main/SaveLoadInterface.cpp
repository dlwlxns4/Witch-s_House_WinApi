#include "SaveLoadInterface.h"
#include "ImageHelper.h"
#include "Image.h"

#define SAVE_LOAD_COUNTS 4

#define STR_INFO_POSX 22
#define STR_INFO_POSY 22

#define SELECT_PANEL_POSX 16
#define SELECT_PANEL_POSY 78

HRESULT SaveLoadInterface::Init()
{

	Mat callSize = OpencvHelper::ReadImage("Image/UI/ItemInfoPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/ItemInfoPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	infoPanel = ImageManager::GetSingleton()->FindImage("Image/UI/ItemInfoPanel.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/OpacityPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/OpacityPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	opacityPanel = ImageManager::GetSingleton()->FindImage("Image/UI/OpacityPanel.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/SaveLoadPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/SaveLoadPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	saveLoadPanel = ImageManager::GetSingleton()->FindImage("Image/UI/SaveLoadPanel.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/SelectPaenl_2.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/SelectPaenl_2.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	selectPaenl = ImageManager::GetSingleton()->FindImage("Image/UI/SelectPaenl_2.bmp");


	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 0;
	selectFtn = ftn;

	return S_OK;
}

void SaveLoadInterface::Update()
{
	if (UIManager::GetSingleton()->GetIsShowSaveLoad() == true && ftn.SourceConstantAlpha < 100)
	{
		ftn.SourceConstantAlpha += 10;
	}

	if (UIManager::GetSingleton()->GetIsShowSaveLoad() == true)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
		{
			selectNum--;
			if (selectNum < 0)
			{
				selectNum = 3;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			selectNum++;
			if (selectNum > 3)
			{
				selectNum = 0;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_CONTROL))
		{
			UIManager::GetSingleton()->SetIsShowSaveLoad(false);
			UIManager::GetSingleton()->SetIsShowUserInfo(true);
		}

		if (isTransparency)
		{
			selectFtn.SourceConstantAlpha -= 4;
			if (selectFtn.SourceConstantAlpha <= 20)
			{
				isTransparency = false;
			}
		}
		else
		{
			selectFtn.SourceConstantAlpha += 4;
			if (selectFtn.SourceConstantAlpha >= 120)
			{
				isTransparency = true;
			}
		}
	}
}

void SaveLoadInterface::Render(HDC hdc)
{
	if (UIManager::GetSingleton()->GetIsShowSaveLoad() == true)
	{
		BLENDFUNCTION tmp = ftn;
		tmp.SourceConstantAlpha = 100;
		opacityPanel->Render(hdc
			, 0
			, 0
			, 0
			, 0
			, TILE_SIZE * TILE_COUNT_X
			, TILE_SIZE * TILE_COUNT_Y
			, 10
			, 10
			, tmp
		);


		infoPanel->Render(hdc
			, 0
			, 0
			, infoPanel->GetWidth()
			, infoPanel->GetHeight()
			, 0
			, 0
			, infoPanel->GetWidth()
			, infoPanel->GetHeight()
		);

		SetTextColor(hdc, RGB(255, 255, 255));
		string output = "로드할 파일을 선택해주세요.";

		TextOut(hdc, STR_INFO_POSX, STR_INFO_POSY, output.c_str(), (int)output.size());
		for (int i = 0; i < SAVE_LOAD_COUNTS; ++i)
		{
			saveLoadPanel->Render(hdc
				, 0
				, TILE_SIZE * 2 + i * saveLoadPanel->GetHeight()
				, saveLoadPanel->GetWidth()
				, saveLoadPanel->GetHeight()
				, 0
				, 0
				, saveLoadPanel->GetWidth()
				, saveLoadPanel->GetHeight()
			);


			output = "파일 " + to_string(i);
			TextOut(hdc, STR_INFO_POSX, TILE_SIZE * 2 + i * saveLoadPanel->GetHeight() + STR_INFO_POSY, output.c_str(), (int)output.size());
		}

		selectPaenl->Render(hdc
			, SELECT_PANEL_POSX
			, SELECT_PANEL_POSY + saveLoadPanel->GetHeight() * selectNum
			, 0
			, 0
			, selectPaenl->GetWidth()
			, selectPaenl->GetHeight()
			, selectPaenl->GetWidth()
			, selectPaenl->GetHeight()
			, selectFtn
		);
		cout << selectNum << endl;
		SetTextColor(hdc, RGB(0, 0, 0));
	}
}

void SaveLoadInterface::Release()
{
}
