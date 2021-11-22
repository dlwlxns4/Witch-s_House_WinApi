#include "TileObj.h"
#include "Tilemap.h"
#include "Camera.h"


HRESULT TileObj::Init()
{
	for (int i = 0; i < MAP_SIZE_Y; i++)    // y��
	{
		for (int j = 0; j < MAP_SIZE_X; j++)    // x��
		{
			SetRect(&(tile[i][j].rc),
				j * TILE_SIZE, i * TILE_SIZE,
				j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE);
			tile[i][j].frameX = -1;
			tile[i][j].frameY = -1;
		}
	}
	
	return S_OK;
}

void TileObj::Render(HDC hdc)
{

	//for (int i = cameraY; i < TILE_COUNT_Y + cameraY; i++)
	//{
	//	for (int j = cameraX; j < TILE_COUNT_X + cameraX; j++)
	//	{

	//		vecSampleImage[tileInfo[layer_size][i][j].mapIndex]->Render(hdc,
	//			tileInfo[layer_size][i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE * cameraX,
	//			tileInfo[layer_size][i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE * cameraY,
	//			tileInfo[layer_size][i][j].frameX,
	//			tileInfo[layer_size][i][j].frameY);

	//	}
	//}
	for (int i = g_cameraPosY; i <= TILE_COUNT_Y+ g_cameraPosY; i++)
	{
		for (int j = g_cameraPosX; j <= TILE_COUNT_X+ g_cameraPosX; j++)
		{
			vecSampleImage[tile[i][j].mapIndex]->Render(hdc,
				tile[i][j].rc.left + TILE_SIZE / 2 - TILE_SIZE - TILE_SIZE * g_cameraPosX,
				tile[i][j].rc.top + TILE_SIZE / 2 - TILE_SIZE - TILE_SIZE * g_cameraPosY,
				tile[i][j].frameX,
				tile[i][j].frameY);

		}
	}
}

void TileObj::Update()
{
}
