#include "MainGame.h"
#include "Image.h"

#include "Camera.h"

float g_cameraPosX;
float g_cameraPosY;

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	TalkManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->ChangeScene("TilemapToolScene");

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
	TimerManager::GetSingleton()->Update();

	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	// PatBlt

	SceneManager::GetSingleton()->Render(hBackBufferDC);

	//fps Ç¥½Ã.
#ifdef _DEBUG
	TimerManager::GetSingleton()->Render(hBackBufferDC);
#endif

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();

	ImageManager::GetSingleton()->Release();

	KeyManager::GetSingleton()->Release();

	SceneManager::GetSingleton()->Release();

	KillTimer(g_hWnd, 0);
}
