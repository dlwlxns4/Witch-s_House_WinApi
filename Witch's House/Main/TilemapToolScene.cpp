#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include <iterator>
#include <filesystem>
#include <opencv2/highgui.hpp>
#include "Button.h"
#include "Layer.h"
#include "TileObj.h"
#include "Camera.h"
#include "PlayerObj.h"

vector<string> mapName;
vector<Image*> vecSampleImage;

//vector<Image*> vecLayerBtnImage;
//vector<string> btnName;



vector<Layer*> vecLayer;
vector<TileObj*> vecTileObj;
PlayerObj* playerObj = nullptr;

using namespace cv;



HRESULT TilemapToolScene::Init()
{
	string dir2 = "Image/Graphics/";
	for (auto& p : filesystem::directory_iterator(dir2))
	{
		string inFolder = p.path().string() + '/';
		for (auto& p2 : filesystem::directory_iterator(inFolder))
		{

			mapName.push_back(p2.path().string());
			cout << p2.path().string() << endl;

			Mat img = imread(p2.path().string());
			vecSampleImage.push_back(ImageManager::GetSingleton()->AddImage(p2.path().string().c_str(), img.cols, img.rows, img.cols / TILE_SIZE, img.rows / TILE_SIZE, true, RGB(255, 0, 255)));
		}
	}



	//string dir = "Image/Graphics/Tile/";
	//int i = 0;
	//for (auto& p : filesystem::directory_iterator(dir))
	//{
	//	mapName.push_back(p.path().string());

	//	Mat img = imread(p.path().string());
	//	vecSampleImage.push_back(ImageManager::GetSingleton()->AddImage(p.path().string().c_str(), img.cols, img.rows, img.cols / TILE_SIZE, img.rows / TILE_SIZE, true, RGB(255, 0, 255)));
	//}

	SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

	sampleImage = vecSampleImage[0];
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



	//레이어 버튼 초기화
	layerAddBtn = new Button;
	layerAddBtn->Init(Button_Type::LayerButton, TILE_SIZE * TILE_COUNT_X + 90, 30, vecLayerBtnImage[0]);

	currentLayer = 0;


	//타일 오브제
	tileObj = new TileObj;
	tileObj->Init();
	vecTileObj.push_back(tileObj);
	vecLayer.push_back(new Layer);
	vecLayer[currLayer]->PushGameObject(vecTileObj[currLayer]);

	//타일스테이트 
	tileState = TileState::Tile;

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

		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			startPosX = (g_ptMouse.x - sampleArea.left) / TILE_SIZE;
			startPosY = (g_ptMouse.y - sampleArea.top) / TILE_SIZE;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			selectPos.clear();

			int posX = g_ptMouse.x - sampleArea.left;
			selectedIdX = posX / TILE_SIZE;

			int posY = g_ptMouse.y - sampleArea.top;
			selectedIdY = posY / TILE_SIZE;
			selectPos.emplace_back(startPosX, startPosY);
			selectPos.emplace_back(selectedIdX, selectedIdY);


			selectedSampleTile.frameX =
				sampleTileInfo[selectedIdY][selectedIdX].frameX;
			selectedSampleTile.frameY =
				sampleTileInfo[selectedIdY][selectedIdX].frameY;
		}
	}


	sampleArea.left = 0;
	sampleArea.top = 0;
	sampleArea.right = TILE_SIZE * TILE_COUNT_X;
	sampleArea.bottom = TILE_SIZE * TILE_COUNT_Y;
	if (tileState == TileState::Tile)
	{
		if (PtInRect(&(sampleArea), g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				startPosX = (g_ptMouse.x - sampleArea.left) / TILE_SIZE + g_cameraPosX + 1;
				startPosY = (g_ptMouse.y - sampleArea.top) / TILE_SIZE + g_cameraPosY + 1;

				int interverX = 0, interverY = 0;
				if (selectPos.empty() == false)
				{
					for (int i = selectPos[0].second; i <= selectPos[1].second; ++i)
					{
						for (int j = selectPos[0].first; j <= selectPos[1].first; ++j)
						{
							vecTileObj[currLayer]->SetTile(startPosX + interverX++, startPosY + interverY, j, i, mapIndex);
						}
						interverX = 0;
						interverY++;
					}
				}
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
			{

				startPosX = (g_ptMouse.x - sampleArea.left) / TILE_SIZE + g_cameraPosX + 1;
				startPosY = (g_ptMouse.y - sampleArea.top) / TILE_SIZE + g_cameraPosY + 1;
				vecTileObj[currLayer]->SetTile(startPosX, startPosY, -1, -1);
			}
		}
	}
	else if (tileState == TileState::Playable)
	{
		if (PtInRect(&(sampleArea), g_ptMouse))
		{
			startPosX = (g_ptMouse.x - sampleArea.left) / TILE_SIZE + g_cameraPosX + 1;
			startPosY = (g_ptMouse.y - sampleArea.top) / TILE_SIZE + g_cameraPosY + 1;

			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				if (playerObj == nullptr)
				{
					playerObj = new PlayerObj;
					playerObj->Init(startPosX, startPosY);
					vecLayer[currLayer]->PushGameObject(playerObj);
				}
				else
				{
					playerObj->SetTilePos(startPosX, startPosY);
					cout << startPosX << " " << startPosY << endl;
					cout << "@" << endl;
				}
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
			{

				startPosX = (g_ptMouse.x - sampleArea.left) / TILE_SIZE + g_cameraPosX + 1;
				startPosY = (g_ptMouse.y - sampleArea.top) / TILE_SIZE + g_cameraPosY + 1;
			}
		}
	}


	//if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
	//{
	//	Save();
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
	//{
	//	Load();
	//}

	//타일맵 카메라 이동
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		if (g_cameraPosX > 0)
			g_cameraPosX--;
		cout << g_cameraPosX << " " << g_cameraPosY << endl;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		if (g_cameraPosX < 100)
			g_cameraPosX++;
		cout << g_cameraPosX << " " << g_cameraPosY << endl;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (g_cameraPosY > 0)
			g_cameraPosY--;
		cout << g_cameraPosX << " " << g_cameraPosY << endl;

	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		if (g_cameraPosY < 100)
			g_cameraPosY++;
		cout << g_cameraPosX << " " << g_cameraPosY << endl;

	}

	//샘플 맵 이동
	if (KeyManager::GetSingleton()->IsStayKeyDown('X'))
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
	else if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
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

	if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
	{
		if (tileState == TileState::Trigger)
		{
			tileState = TileState::Playable;
		}
		else if (tileState == TileState::Playable)
		{
			tileState = TileState::Tile;
		}
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('Y'))
	{
		if (tileState == TileState::Tile)
		{
			tileState = TileState::Playable;
		}
		else if (tileState == TileState::Playable)
		{
			tileState = TileState::Trigger;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))
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
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
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

	//버튼
	layerAddBtn->Update();


	if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))
	{
		if (currLayer > 0)
		{
			currLayer--;
		}
		currentLayer = 0;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('2'))
	{
		if (currLayer < vecLayer.size() - 1)
		{
			currLayer++;
		}
		currentLayer = 1;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('3'))
	{
		currentLayer = 2;
	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown('5'))
	{
		currLayer++;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('4'))
	{
		if (currLayer > 1)
			currLayer--;
	}



}

void TilemapToolScene::Render(HDC hdc)
{

	PatBlt(hdc, 0, 0, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y, WHITENESS);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	for (int i = g_cameraPosY; i < TILE_COUNT_Y + g_cameraPosY; i++)
	{
		for (int j = g_cameraPosX; j < TILE_COUNT_X + g_cameraPosX; j++)
		{
			Rectangle(hdc,
				tileInfo[i][j].rc.left - TILE_SIZE * g_cameraPosX,
				tileInfo[i][j].rc.top - TILE_SIZE * g_cameraPosY,
				tileInfo[i][j].rc.right - TILE_SIZE * g_cameraPosX,
				tileInfo[i][j].rc.bottom - TILE_SIZE * g_cameraPosY);
		}
	}






	for (int i = 0; i < vecLayer.size(); ++i)
	{
		vecLayer[i]->Render(hdc);
	}




	// 메인 영역
	//for (int layer_size = 0; layer_size < 3; layer_size++)
	//{
	//	for (int i = cameraY; i < TILE_COUNT_Y + cameraY; i++)
	//	{
	//		for (int j = cameraX; j < TILE_COUNT_X + cameraX; j++)
	//		{
	//			
	//			vecSampleImage[tileInfo[layer_size][i][j].mapIndex]->Render(hdc,
	//				tileInfo[layer_size][i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
	//				tileInfo[layer_size][i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
	//				tileInfo[layer_size][i][j].frameX,
	//				tileInfo[layer_size][i][j].frameY);

	//			//sampleImage->Render(hdc,
	//			//	tileInfo[i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
	//			//	tileInfo[i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
	//			//	tileInfo[i][j].frameX,
	//			//	tileInfo[i][j].frameY);
	//		}
	//	}
	//}





	// 샘플 영역
	sampleImage->Render(hdc,
		TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
		sampleImage->GetHeight() / 2);



	for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y축
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)    // x축
		{
			Rectangle(hdc,
				sampleTileInfo[i][j].rc.left,
				sampleTileInfo[i][j].rc.top,
				sampleTileInfo[i][j].rc.right,
				sampleTileInfo[i][j].rc.bottom
			);

		}
	}
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);


	// 선택된 타일
	if (selectPos.empty() == false)
	{
		int interverX = 0, interverY = 0;
		for (int i = selectPos[0].second; i <= selectPos[1].second; ++i)
		{
			for (int j = selectPos[0].first; j <= selectPos[1].first; ++j)
			{
				sampleImage->Render(hdc, TILE_SIZE * TILE_COUNT_X + 50 + (TILE_SIZE * interverX++), 100 + (TILE_SIZE * interverY),
					j, i, 1.0f);
			}
			interverX = 0;
			interverY++;
		}
	}

	TextOut(hdc, 50, TILEMAPTOOL_SIZE_Y - 30, TEXT("Current SampleTile : "), 20);
	TextOut(hdc, 250, TILEMAPTOOL_SIZE_Y - 30, mapName[mapIndex].c_str(), mapName[mapIndex].size());

	TextOut(hdc, 200, TILEMAPTOOL_SIZE_Y - 70, TEXT("Max Layer : "), 12);
	TextOut(hdc, 400, TILEMAPTOOL_SIZE_Y - 70, to_string(vecLayer.size()).c_str(), (int)to_string(vecLayer.size()).size());

	TextOut(hdc, 200, TILEMAPTOOL_SIZE_Y - 50, TEXT("Current Layer : "), 16);
	TextOut(hdc, 400, TILEMAPTOOL_SIZE_Y - 50, to_string(currLayer + 1).c_str(), (int)to_string(currLayer + 1).size());

	TextOut(hdc, 200, TILEMAPTOOL_SIZE_Y - 90, TEXT("TileState : "), 12);

	TextOut(hdc, 400, TILEMAPTOOL_SIZE_Y - 90, TileStateToString(tileState).c_str(), TileStateToString(tileState).size());




	//Btn
	layerAddBtn->Render(hdc);
}

void TilemapToolScene::Release()
{

	//레이어 메모리 해제
	for (auto iter : vecLayer)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}

	SAFE_DELETE(layerAddBtn);
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

const string TilemapToolScene::TileStateToString(TileState e) throw()
{
	switch (e)
	{
	case TileState::Tile:
		return "Tile";
	case TileState::Playable:
		return "Playable";
	case TileState::Trigger:
		return "Trigger";
	default: throw std::invalid_argument("Unimplemented item");
	}
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
