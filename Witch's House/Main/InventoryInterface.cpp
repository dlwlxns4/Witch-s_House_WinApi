#include "InventoryInterface.h"
#include "ImageHelper.h"
#include "Image.h"

#include "Input.h"

#define INVENTORY_START_POSY 9

HRESULT InventoryInterface::Init()
{
	Mat callSize = OpencvHelper::ReadImage("Image/UI/ItemInfoPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/ItemInfoPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	itemInfoPanel = ImageManager::GetSingleton()->FindImage("Image/UI/ItemInfoPanel.bmp");


	callSize = OpencvHelper::ReadImage("Image/UI/InventoryPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/InventoryPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	inventoryPaenl = ImageManager::GetSingleton()->FindImage("Image/UI/InventoryPanel.bmp");

	callSize = OpencvHelper::ReadImage("Image/UI/OpacityPanel.bmp");
	ImageManager::GetSingleton()->AddImage("Image/UI/OpacityPanel.bmp", callSize.cols, callSize.rows, 1, 1, true, RGB(255, 0, 255));
	opacityPanel = ImageManager::GetSingleton()->FindImage("Image/UI/OpacityPanel.bmp");

	ftn.AlphaFormat = 0;
	ftn.BlendFlags = 0;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.SourceConstantAlpha = 0;

	return S_OK;
}

void InventoryInterface::Update()
{
	if (UIManager::GetSingleton()->GetIsShowInventory() == true && ftn.SourceConstantAlpha < 100)
	{
		ftn.SourceConstantAlpha += 10;
	}

	if (UIManager::GetSingleton()->GetIsShowInventory() == true)
	{
		if (Input::GetButton(VK_CONTROL))
		{
			ftn.SourceConstantAlpha = 0;
			UIManager::GetSingleton()->SetIsShowInventory(false);
			UIManager::GetSingleton()->SetIsShowUserInfo(true);
		}
	}
}

void InventoryInterface::Render(HDC hdc)
{
	if ( UIManager::GetSingleton()->GetIsShowInventory() == true)
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


		itemInfoPanel->Render(hdc
			, 0
			, 0
			, itemInfoPanel->GetWidth()
			, itemInfoPanel->GetHeight()
			, 0
			, 0
			, itemInfoPanel->GetWidth()
			, itemInfoPanel->GetHeight()
		);

		inventoryPaenl->Render(hdc
			, 0
			, TILE_SIZE*INVENTORY_START_POSY
			, inventoryPaenl->GetWidth()
			, inventoryPaenl->GetHeight()
			, 0
			, 0
			, inventoryPaenl->GetWidth()
			, inventoryPaenl->GetHeight()
		);
	}
}

void InventoryInterface::Release()
{
}
