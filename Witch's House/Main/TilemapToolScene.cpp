#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TilemapToolScene::Init()
{


    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/Tile0.bmp",
        160, 64, 5, 2, true, RGB(255, 255, 255));
    cout << TILE_SIZE << endl;

    if (sampleImage == nullptr)
    {
        cout << "Image/Tile0.bmp �ε� ����!!" << endl; 
        return E_FAIL;
    }

    // ���� ��� ���� ���� �ʱ�ȭ
    for (int i = 0; i < TILE_COUNT_Y; i++)    // y��
    {
        for (int j = 0; j < TILE_COUNT_X; j++)    // x��
        {
            SetRect(&(tileInfo[i][j].rc),
                j * TILE_SIZE , i * TILE_SIZE,
                j * TILE_SIZE + TILE_SIZE , i * TILE_SIZE + TILE_SIZE);

            tileInfo[i][j].frameX = 0;
            tileInfo[i][j].frameY = 0;


        }
    }

    // ������ ��� ���� ���� �ʱ�ȭ
    for (int i = 0; i < SAMPLE_TILE_COUNT_Y; i++)    // y��
    {
        for (int j = 0; j < SAMPLE_TILE_COUNT_X; j++)    // x��
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
    for (int j = 0; j < TILE_COUNT_Y; j++)
    {
        for (int i = 0; i < TILE_COUNT_X; i++)
        {
       
            if (PtInRect(&(tileInfo[j][i].rc), g_ptMouse))
            {
                if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
                {
                    tileInfo[j][i].frameX = selectedSampleTile.frameX;
                    tileInfo[j][i].frameY = selectedSampleTile.frameY;
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
    if (KeyManager::GetSingleton()->IsOnceKeyUp('W'))
    {
        if (bShowNoneWalkable)
        {
            bShowNoneWalkable = false;
        }
        else
        {
            bShowNoneWalkable = true;
        }
    }
    if (KeyManager::GetSingleton()->IsOnceKeyUp('E'))
    {
        if (bShowBodyCollider)
        {
            bShowBodyCollider = false;
        }
        else
        {
            bShowBodyCollider = true;
        }
    }
    
}

void TilemapToolScene::Render(HDC hdc)
{


    HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

    // ���� ����
    for (int i = 0; i < TILE_COUNT_Y; i++)
    {
        for (int j = 0; j < TILE_COUNT_X; j++)
        {
            Rectangle(hdc, tileInfo[i][j].rc.left, tileInfo[i][j].rc.top, tileInfo[i][j].rc.right, tileInfo[i][j].rc.bottom);


            sampleImage->Render(hdc,
                tileInfo[i][j].rc.left + TILE_SIZE / 2,
                tileInfo[i][j].rc.top + TILE_SIZE / 2,
                tileInfo[i][j].frameX,
                tileInfo[i][j].frameY);

        }
    }

    SelectObject(hdc, oldBrush);
    DeleteObject(myBrush);



    // ���� ����
    sampleImage->Render(hdc,
        TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
        sampleImage->GetHeight() / 2);



    PatBlt(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2 - 32, sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 + 148, 112,112, WHITENESS);
    // ���õ� Ÿ��
    sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2,
        sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 + 180,
        selectedSampleTile.frameX, selectedSampleTile.frameY, 2.5f);
    
    

}

void TilemapToolScene::Release()
{

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
    if ( ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &readByte, NULL) == false )
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}
