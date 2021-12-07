#include "MainGame.h"
#include "Image.h"

#include "Camera.h"

#include "Input.h"

float g_cameraPosX;
float g_cameraPosY;

HRESULT MainGame::Init()
{
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	TalkManager::GetSingleton()->Init();
	UIManager::GetSingleton()->Init();


	SceneManager::GetSingleton()->ChangeScene("TilemapToolScene");

	Input::Init(g_hWnd);

	srand((unsigned int)time(nullptr));

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	backBuffer = new Image;
	int maxSizeX = WIN_SIZE_X > TILEMAPTOOL_SIZE_X ? WIN_SIZE_X : TILEMAPTOOL_SIZE_X;
	int maxSizeY = WIN_SIZE_Y > TILEMAPTOOL_SIZE_Y ? WIN_SIZE_Y : TILEMAPTOOL_SIZE_Y;

	backBuffer->Init("Image/mapImage.bmp", maxSizeX, maxSizeY);
	return S_OK;
}

void MainGame::Update()
{
	Input::Update();

	TimerManager::GetSingleton()->Update();

	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HFONT hFont = CreateFont(
		20,
		0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼나무")
	);
	HDC hBackBufferDC = backBuffer->GetMemDC();
	HFONT oldFont = (HFONT)SelectObject(hBackBufferDC, hFont);
	SetBkMode(hBackBufferDC, TRANSPARENT);

	// PatBlt
	PatBlt(hBackBufferDC, 0, 0, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y, WHITENESS);


	SceneManager::GetSingleton()->Render(hBackBufferDC);
	//fps 표시.
#ifdef _DEBUG
	TimerManager::GetSingleton()->Render(hBackBufferDC);
#endif

	backBuffer->Render(hdc);


	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();

	ImageManager::GetSingleton()->Release();


	SceneManager::GetSingleton()->Release();

	KillTimer(g_hWnd, 0);
}
