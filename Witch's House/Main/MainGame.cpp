#include "MainGame.h"
#include "Image.h"


HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

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

	SceneManager::GetSingleton()->Render(hBackBufferDC);

	//fps 표시.
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


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int i;
	TCHAR str[128];


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:		

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COMBOBOX:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:	// 리스트박스와 구성이 같음
				i = SendMessage(g_hWndComboBox, CB_GETCURSEL, 0, 0);
				SendMessage(g_hWndComboBox, CB_GETLBTEXT, i, (LPARAM)str);
				cout << str << endl;
				//SetWindowText(hWnd, str);
				break;
			case CBN_EDITCHANGE:	// 에디트 박스에 대한 처리
				GetWindowText(g_hWndComboBox, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
