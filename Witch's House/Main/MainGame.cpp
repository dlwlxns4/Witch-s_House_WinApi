#include "MainGame.h"
#include "Image.h"

#include "Camera.h"

#include "Input.h"

float g_cameraPosX;
float g_cameraPosY;



HRESULT MainGame::Init()
{
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	TalkManager::GetSingleton()->Init();
	UIManager::GetSingleton()->Init();


	SceneManager::GetSingleton()->ChangeScene("TilemapToolScene");

	Input::Init(g_hWnd);


	backBuffer = new Image;
	int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;

	backBuffer->Init("Image/mapImage.bmp", maxSizeX, maxSizeY);
	return S_OK;
}

void MainGame::Update()
{
	Input::Update();

	if (Input::GetButton('A'))
	{
		cout << "@" << endl;
	}
	SceneManager::GetSingleton()->Update();

	//InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HFONT hFont = CreateFont(
		20,
		0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("?޸ճ???")
	);
	HDC hBackBufferDC = backBuffer->GetMemDC();
	HFONT oldFont = (HFONT)SelectObject(hBackBufferDC, hFont);
	SetBkMode(hBackBufferDC, TRANSPARENT);

	// PatBlt
	PatBlt(hBackBufferDC, 0, 0, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y, WHITENESS);


	SceneManager::GetSingleton()->Render(hBackBufferDC);
	//fps ǥ??.
#ifdef _DEBUG
#endif

	backBuffer->Render(hdc);


	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	ImageManager::GetSingleton()->Release();

	SceneManager::GetSingleton()->Release();
}
