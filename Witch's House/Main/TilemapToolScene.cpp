#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include <iterator>
#include <filesystem>
#include <opencv2/highgui.hpp>
#include "Button.h"

vector<string> mapName;
vector<Image*> vecSampleImage;

//vector<Image*> vecLayerBtnImage;
//vector<string> btnName;

using namespace cv;

HRESULT TilemapToolScene::Init()
{

	string dir = "Image/Graphics/Tile/";
	int i = 0;
	for (auto& p : filesystem::directory_iterator(dir))
	{
		mapName.push_back(p.path().string().substr());

		Mat img = imread(p.path().string());
		vecSampleImage.push_back(ImageManager::GetSingleton()->AddImage(p.path().string().c_str(), img.cols, img.rows, img.cols / TILE_SIZE, img.rows / TILE_SIZE, true, RGB(255, 0, 255)));
	}

	SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

	sampleImage = ImageManager::GetSingleton()->FindImage("Image/Graphics/Tile/Tile0.bmp");
	SAMPLE_TILE_X = sampleImage->GetWidth() / TILE_SIZE;
	SAMPLE_TILE_Y = sampleImage->GetHeight() / TILE_SIZE;

	if (sampleImage == nullptr)
	{
		cout << "Image/Tile0.bmp �ε� ����!!" << endl;
		return E_FAIL;
	}

	// ���� ��� ���� ���� �ʱ�ȭ
	for (int layer_size = 0; layer_size < LAYER_SIZE; layer_size++)
	{

		for (int i = 0; i < MAP_SIZE_Y; i++)    // y��
		{
			for (int j = 0; j < MAP_SIZE_X; j++)    // x��
			{
				SetRect(&(tileInfo[layer_size][i][j].rc),
					j * TILE_SIZE, i * TILE_SIZE,
					j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE);

				tileInfo[layer_size][i][j].frameX = -1;
				tileInfo[layer_size][i][j].frameY = -1;


			}
		}
	}

	// ������ ��� ���� ���� �ʱ�ȭ
	for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y��
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)    // x��
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

	// ���õ� Ÿ��
	selectedSampleTile.frameX = 0;
	selectedSampleTile.frameY = 0;



	//���̾� ��ư �ʱ�ȭ
	layerBtn = new Button[3];
	for (int i = 0; i < 3; ++i)
	{
		cout << vecLayerBtnImage[0] << endl;
		layerBtn[i].Init(Button_Type::LayerButton, TILE_SIZE * TILE_COUNT_X + 50 + BTN_SIZE_X * i, 200, vecLayerBtnImage[i]);
	}
	layerBtn[0].SetAtive(true);
	currentLayer = 0;


	return S_OK;
}

void TilemapToolScene::Update()
{
	// ���ÿ������� ������ ����
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

	// ���ο������� ���õ� ���� ������ ����

	for (int j = cameraY; j < TILE_COUNT_Y + cameraY; j++)
	{
		for (int i = cameraX; i < TILE_COUNT_X + cameraX; i++)
		{
			POINT mousePos{ g_ptMouse.x + cameraX * TILE_SIZE ,g_ptMouse.y + cameraY * TILE_SIZE };
			if (PtInRect(&(tileInfo[currentLayer][j][i].rc), mousePos))
			{
				if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
				{
					tileInfo[currentLayer][j][i].frameX = selectedSampleTile.frameX;
					tileInfo[currentLayer][j][i].frameY = selectedSampleTile.frameY;
					tileInfo[currentLayer][j][i].mapIndex = mapIndex;
					break;
				}
				else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
				{
					tileInfo[currentLayer][j][i].frameX = -1;
					tileInfo[currentLayer][j][i].frameY = -1;
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

	//Ÿ�ϸ� ī�޶� �̵�
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

	//���� �� �̵�
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
	{
		if (mapIndex < mapName.size() - 1)
		{
			mapIndex++;
			cout << mapName[mapIndex] << endl;
			sampleImage = ImageManager::GetSingleton()->FindImage(mapName[mapIndex].c_str());
			SAMPLE_TILE_X = sampleImage->GetWidth() / TILE_SIZE;
			SAMPLE_TILE_Y = sampleImage->GetHeight() / TILE_SIZE;
			for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y��
			{
				for (int j = 0; j < SAMPLE_TILE_X; j++)    // x��
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
			for (int i = 0; i < SAMPLE_TILE_Y; i++)    // y��
			{
				for (int j = 0; j < SAMPLE_TILE_X; j++)    // x��
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

	//��ư
	for (int i = 0; i < 3; ++i)
	{
		layerBtn[i].Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))
	{
		currentLayer = 0;
		layerBtn[0].SetAtive(true);
		layerBtn[1].SetAtive(false);
		layerBtn[2].SetAtive(false);
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('2'))
	{
		currentLayer = 1;
		layerBtn[0].SetAtive(false);
		layerBtn[1].SetAtive(true);
		layerBtn[2].SetAtive(false);
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('3'))
	{
		currentLayer = 2;
		layerBtn[0].SetAtive(false);
		layerBtn[1].SetAtive(false);
		layerBtn[2].SetAtive(true);
	}

	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('5'))
	{
		currLayer++;
	}
	else if(KeyManager::GetSingleton()->IsOnceKeyDown('4'))
	{
		if(currLayer>1)
			currLayer--;
	}



}

void TilemapToolScene::Render(HDC hdc)
{

	PatBlt(hdc, 0, 0, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y, WHITENESS);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);



	for (int i = cameraY; i < TILE_COUNT_Y + cameraY; i++)
	{
		for (int j = cameraX; j < TILE_COUNT_X + cameraX; j++)
		{
			Rectangle(hdc,
				tileInfo[0][i][j].rc.left - TILE_SIZE * cameraX,
				tileInfo[0][i][j].rc.top - TILE_SIZE * cameraY,
				tileInfo[0][i][j].rc.right - TILE_SIZE * cameraX,
				tileInfo[0][i][j].rc.bottom - TILE_SIZE * cameraY);
		}
	}
	


	// ���� ����
	for (int layer_size = 0; layer_size < 3; layer_size++)
	{
		for (int i = cameraY; i < TILE_COUNT_Y + cameraY; i++)
		{
			for (int j = cameraX; j < TILE_COUNT_X + cameraX; j++)
			{
				
				vecSampleImage[tileInfo[layer_size][i][j].mapIndex]->Render(hdc,
					tileInfo[layer_size][i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
					tileInfo[layer_size][i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
					tileInfo[layer_size][i][j].frameX,
					tileInfo[layer_size][i][j].frameY);

				//sampleImage->Render(hdc,
				//	tileInfo[i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
				//	tileInfo[i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
				//	tileInfo[i][j].frameX,
				//	tileInfo[i][j].frameY);
			}
		}
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);



	// ���� ����
	sampleImage->Render(hdc,
		TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
		sampleImage->GetHeight() / 2);



	// ���õ� Ÿ��
	sampleImage->Render(hdc, TILE_SIZE * TILE_COUNT_X + 50, 100,
		selectedSampleTile.frameX, selectedSampleTile.frameY, 2.5f);

	TextOut(hdc, 50, TILEMAPTOOL_SIZE_Y - 30, TEXT("Current SampleTile : "), 20);
	TextOut(hdc, 250, TILEMAPTOOL_SIZE_Y - 30, mapName[mapIndex].c_str(), mapName[mapIndex].size());

	TextOut(hdc, 400, TILEMAPTOOL_SIZE_Y -50, to_string(currLayer).c_str(), to_string(currLayer).size());



	//Btn
	for (int i = 0; i < 3; ++i)
	{
		layerBtn[i].Render(hdc);
	}
}

void TilemapToolScene::Release()
{

	SAFE_DELETE_ARRAY(layerBtn);

}

void TilemapToolScene::Save(int saveIndex)
{
	string filePath = "Save/saveMapData" + to_string(saveIndex) + ".map";


	HANDLE hFile = CreateFile(filePath.c_str(),
		GENERIC_WRITE,                  //�б�, ���� Ÿ��
		0, NULL,                        //����, ���� ���
		CREATE_ALWAYS,                  //������ ����ų� ���� �� �ɼ�
		FILE_ATTRIBUTE_NORMAL,          //���� �Ӽ�(�б� ����, ���� ���)
		NULL);                          //

	//����
	DWORD writtenByte;
	if (WriteFile(hFile,                                    //���� �ڵ�
		tileInfo,                                       // �޸� ���� �ּ�
		sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // �޸� ũ��
		&writtenByte,                                   // ���� ������ ���� �뷮
		NULL) == false)
	{
		MessageBox(g_hWnd, "�� ������ ���忡 �����߽��ϴ�.", "����", MB_OK);
	}

	CloseHandle(hFile);
}

void TilemapToolScene::Load(int loadIndex)
{
	string filePath = "Save/saveMapData" + to_string(loadIndex) + ".map";

	HANDLE hFile = CreateFile(filePath.c_str(),
		GENERIC_READ,                  //�б�, ���� Ÿ��
		0, NULL,                        //����, ���� ���
		OPEN_EXISTING,                  //������ ����ų� ���� �� �ɼ�
		FILE_ATTRIBUTE_NORMAL,          //���� �Ӽ�(�б� ����, ���� ���)
		NULL);                          //

	//�б�

	DWORD readByte;
	if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false)
	{
		MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
	}

	CloseHandle(hFile);
}
