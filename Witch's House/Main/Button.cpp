#include "Button.h"
#include "Image.h"
#include "ImageHelper.h"

#include "Tilemap.h"
#include "Layer.h"
#include "TileObj.h"

#include "Input.h"

bool g_isBtnActive;
HRESULT Button::Init()
{
	return E_NOTIMPL;
}

HRESULT Button::Init(Button_Type type, int posX, int posY, Image* image)
{
	//pF = AddNum;

	//int c = AddNum(10, 20);
	//int d = pF(10, 20);

	//pF = MinusNum;
	//d = pF(10, 20);



	type = type;
	img = image;
	pos.x = (float)posX;
	pos.y = (float)posY;

	shape.left = (LONG)pos.x - img->GetFrameWidth() / 2;
	shape.right = (LONG)pos.x + img->GetFrameWidth() / 2;
	shape.top = (LONG)pos.y - img->GetFrameHeight() / 2;
	shape.bottom = (LONG)pos.y + img->GetFrameHeight() / 2;

	state = Button_State::None;

	return S_OK;
}

void Button::Update()
{
	g_isBtnActive = false;

	// 마우스 커서가 충돌영역에 들어갔는지
	if (PtInRect(&shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			state = Button_State::Down;
		}
		else if (Input::GetButtonUp(VK_LBUTTON) && state == Button_State::Down)
		{
			state = Button_State::Up;


			//// 버튼 기능 수행 (함수포인터를 활용)
			//funcPtr();

			//if (bf && pFunc)
			//	(bf->*pFunc)(arg);
			switch (type)
			{
			case Button_Type::LayerButton:
				AddLayer();

				break;
			case Button_Type::GotoResult:
				break;
			case Button_Type::Close:
				Release();
				break;
			}
			return;
		}
	}
	else
	{
		state = Button_State::None;
	}
}

void Button::AddLayer()
{
	//TileObj* tileObject = new TileObj;
	//tileObject->Init();
	//vecTileObj.push_back(tileObject);
	//vecLayer.push_back(new Layer);
	//vecLayer[vecLayer.size() - 1]->PushGameObject(vecTileObj[vecTileObj.size() - 1]);

	vecLayer.push_back(new Layer);

}
void Button::Render(HDC hdc)
{

	switch (state)
	{
	case Button_State::None:
	case Button_State::Up:
		if (img)
			img->Render(hdc, (int)pos.x, (int)pos.y, 0, 0);
		break;
	case Button_State::Down:
		if (img)
			img->Render(hdc, (int)pos.x, (int)pos.y, 1, 0);
		break;
	}



	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
}

void Button::Release()
{

}
