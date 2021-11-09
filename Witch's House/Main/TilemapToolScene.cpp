#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include <iterator>
#include <filesystem>
#include <opencv2/highgui.hpp>

vector<string> mapName;
vector<Image*> vecSampleImage;

using namespace cv;

HRESULT TilemapToolScene::Init()
{
	string dir = "Image/Graphics/Tile/";
	int i = 0;
	for (auto& p : filesystem::directory_iterator(dir))
	{
		//mapName.push_back(p.path().string().substr(p.path().string().find('\\') + 1, p.path().string().size()));
		mapName.push_back(p.path().string().substr());

		cout << p.path().string().substr() << endl;
		Mat img = imread(p.path().string());
		cout << img.rows << " " <<  img.cols << endl;
		vecSampleImage.push_back(ImageManager::GetSingleton()->AddImage(p.path().string().c_str(), img.cols, img.rows, img.cols / TILE_SIZE, img.rows / TILE_SIZE, true, RGB(255, 255, 255)));
	}

	SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

	sampleImage = ImageManager::GetSingleton()->FindImage("Image/Graphics/Tile/Tile0.bmp");
	SAMPLE_TILE_X = sampleImage->GetWidth() / TILE_SIZE;
	SAMPLE_TILE_Y = sampleImage->GetHeight() / TILE_SIZE;
	
	if (sampleImage == nullptr)
	{
		cout << "Image/Tile0.bmp 로드 실패!!" << endl;
		return E_FAIL;
	}

	// 왼쪽 상단 메인 영역 초기화
	for (int i = 0; i < MAP_SIZE_Y; i++)    // y축
	{
		for (int j = 0; j < MAP_SIZE_X; j++)    // x축
		{
			SetRect(&(tileInfo[i][j].rc),
				j * TILE_SIZE, i * TILE_SIZE,
				j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE);

			tileInfo[i][j].frameX = -1;
			tileInfo[i][j].frameY = -1;


		}
	}

	// 오른쪽 상단 샘플 영역 초기화
	for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y축
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)    // x축
		{
			SetRect(&(sampleTileInfo[i][j].rc),
				TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
				i * TILE_SIZE,
				TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
				i * TILE_SIZE + TILE_SIZE);


			sampleTileInfo[i][j].frameX = j;
			sampleTileInfo[i][j].frameY = i;
		}
	}

	bShowNoneWalkable = false;
	bShowBodyCollider = false;

	// 선택된 타일
	selectedSampleTile.frameX = 0;
	selectedSampleTile.frameY = 0;

	return S_OK;
}

void TilemapToolScene::Update()
{
	// 샘플영역에서 샘플을 선택
	RECT sampleArea;
	sampleArea.left = TILEMAPTOOL_SIZE_X - sampleImage->GetWidth();
	sampleArea.right = TILEMAPTOOL_SIZE_X;
	sampleArea.top = 0;
	sampleArea.bottom = sampleImage->GetHeight();


	if (PtInRect(&(sampleArea), g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - sampleArea.left;
			selectedIdX = posX / TILE_SIZE;

			int posY = g_ptMouse.y - sampleArea.top;
			selectedIdY = posY / TILE_SIZE;

			selectedSampleTile.frameX =
				sampleTileInfo[selectedIdY][selectedIdX].frameX;
			selectedSampleTile.frameY =
				sampleTileInfo[selectedIdY][selectedIdX].frameY;

			cout << selectedIdX << "  " << selectedIdY << endl;

		}
	}

	// 메인영역에서 선택된 샘플 정보로 수정
	for (int j = cameraY; j < TILE_COUNT_Y + cameraY; j++)
	{
		for (int i = cameraX; i < TILE_COUNT_X + cameraX; i++)
		{
			POINT mousePos{ g_ptMouse.x + cameraX * TILE_SIZE ,g_ptMouse.y + cameraY * TILE_SIZE };
			if (PtInRect(&(tileInfo[j][i].rc), mousePos))
			{
				if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
				{
					tileInfo[j][i].frameX = selectedSampleTile.frameX;
					tileInfo[j][i].frameY = selectedSampleTile.frameY;
					tileInfo[j][i].mapIndex = mapIndex;
					break;
				}
				else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
				{
					tileInfo[j][i].frameX = -1;
					tileInfo[j][i].frameY = -1;
					break;
				}
			}
		}
	}




	if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
	{
		Save();
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
	{
		Load();
	}
	//if (KeyManager::GetSingleton()->IsOnceKeyUp('W'))
	//{
	//    if (bShowNoneWalkable)
	//    {
	//        bShowNoneWalkable = false;
	//    }
	//    else
	//    {
	//        bShowNoneWalkable = true;
	//    }
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyUp('E'))
	//{
	//    if (bShowBodyCollider)
	//    {
	//        bShowBodyCollider = false;
	//    }
	//    else
	//    {
	//        bShowBodyCollider = true;
	//    }
	//}
	//

	//타일맵 카메라 이동
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		if (cameraX > 0)
			cameraX--;
		cout << cameraX << " " << cameraY << endl;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		if (cameraX < 100)
			cameraX++;
		cout << cameraX << " " << cameraY << endl;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (cameraY > 0)
			cameraY--;
		cout << cameraX << " " << cameraY << endl;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		if (cameraY < 100)
			cameraY++;
		cout << cameraX << " " << cameraY << endl;

	}

	//샘플 맵 이동
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
	{
		if (mapIndex < mapName.size() - 1)
		{
			mapIndex++;
			cout << mapName[mapIndex] << endl;
			sampleImage = ImageManager::GetSingleton()->FindImage(mapName[mapIndex].c_str());
			SAMPLE_TILE_X = sampleImage->GetWidth() / TILE_SIZE;
			SAMPLE_TILE_Y = sampleImage->GetHeight() / TILE_SIZE;
			for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y축
			{
				for (int j = 0; j < SAMPLE_TILE_X; j++)    // x축
				{
					SetRect(&(sampleTileInfo[i][j].rc),
						TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
						i * TILE_SIZE,
						TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
						i * TILE_SIZE + TILE_SIZE);
										
					sampleTileInfo[i][j].frameX = j;
					sampleTileInfo[i][j].frameY = i;
				}
			}
		}
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	{
		if (mapIndex > 0)
		{
			mapIndex--;
			cout << mapName[mapIndex] << endl;
			sampleImage = ImageManager::GetSingleton()->FindImage(mapName[mapIndex].c_str());
			SAMPLE_TILE_X = sampleImage->GetWidth() / TILE_SIZE;
			SAMPLE_TILE_Y = sampleImage->GetHeight() / TILE_SIZE;
			for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y축
			{
				for (int j = 0; j < SAMPLE_TILE_X; j++)    // x축
				{
					SetRect(&(sampleTileInfo[i][j].rc),
						TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
						i * TILE_SIZE,
						TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
						i * TILE_SIZE + TILE_SIZE);


					sampleTileInfo[i][j].frameX = j;
					sampleTileInfo[i][j].frameY = i;
				}
			}

		}
	}


}

void TilemapToolScene::Render(HDC hdc)
{

	PatBlt(hdc, 0, 0, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y, WHITENESS);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	// 메인 영역
	for (int i = cameraY; i < TILE_COUNT_Y + cameraY; i++)
	{
		for (int j = cameraX; j < TILE_COUNT_X + cameraX; j++)
		{
			Rectangle(hdc,
				tileInfo[i][j].rc.left - TILE_SIZE * cameraX,
				tileInfo[i][j].rc.top - TILE_SIZE * cameraY,
				tileInfo[i][j].rc.right - TILE_SIZE * cameraX,
				tileInfo[i][j].rc.bottom - TILE_SIZE * cameraY);

			vecSampleImage[tileInfo[i][j].mapIndex]->Render(hdc,
				tileInfo[i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
				tileInfo[i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
				tileInfo[i][j].frameX,
				tileInfo[i][j].frameY);

			//sampleImage->Render(hdc,
			//	tileInfo[i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
			//	tileInfo[i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
			//	tileInfo[i][j].frameX,
			//	tileInfo[i][j].frameY);

		}
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);



	// 샘플 영역
	sampleImage->Render(hdc,
		TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
		sampleImage->GetHeight() / 2);



	// 선택된 타일
	sampleImage->Render(hdc,TILE_SIZE*TILE_COUNT_X+50, 100,
		selectedSampleTile.frameX, selectedSampleTile.frameY, 2.5f);

	TextOut(hdc, 50, TILEMAPTOOL_SIZE_Y - 30, TEXT("Current SampleTile : "), 20);
	TextOut(hdc, 250, TILEMAPTOOL_SIZE_Y - 30, mapName[mapIndex].c_str(), mapName[mapIndex].size());

}

void TilemapToolScene::Release()
{

}

void TilemapToolScene::Save(int saveIndex)
{
	string filePath = "Save/saveMapData" + to_string(saveIndex) + ".map";


	HANDLE hFile = CreateFile(filePath.c_str(),
		GENERIC_WRITE,                  //읽기, 쓰기 타입
		0, NULL,                        //공유, 보안 모드
		CREATE_ALWAYS,                  //파일을 만들거나 읽을 때 옵션
		FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
		NULL);                          //

	//쓰기
	DWORD writtenByte;
	if (WriteFile(hFile,                                    //파일 핸들
		tileInfo,                                       // 메모리 시작 주소
		sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // 메모리 크기
		&writtenByte,                                   // 실제 쓰여진 파일 용량
		NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
	}

	CloseHandle(hFile);
}

void TilemapToolScene::Load(int loadIndex)
{
	string filePath = "Save/saveMapData" + to_string(loadIndex) + ".map";

	HANDLE hFile = CreateFile(filePath.c_str(),
		GENERIC_READ,                  //읽기, 쓰기 타입
		0, NULL,                        //공유, 보안 모드
		OPEN_EXISTING,                  //파일을 만들거나 읽을 때 옵션
		FILE_ATTRIBUTE_NORMAL,          //파일 속성(읽기 전용, 숨김 등등)
		NULL);                          //

	//읽기

	DWORD readByte;
	if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false)
	{
		MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
	}

	CloseHandle(hFile);
}
