#include "TriggerObj.h"
#include "Tilemap.h"
#include "Camera.h"

HRESULT TriggerObj::Init()
{
	return S_OK;
}

void TriggerObj::Render(HDC hdc)
{
	vecSampleImage[tile.mapIndex]->Render(hdc,
		tile.rc.left + TILE_SIZE / 2 - TILE_SIZE * g_cameraPosX,
		tile.rc.top + TILE_SIZE / 2 - TILE_SIZE * g_cameraPosY,
		tile.frameX,
		tile.frameY
	);

	if (tile.rc.left - TILE_SIZE * g_cameraPosX < TILE_SIZE * TILE_COUNT_X &&
		tile.rc.top - TILE_SIZE * g_cameraPosY < TILE_SIZE * TILE_COUNT_Y)
	{
		TextOut(hdc, tile.rc.left - TILE_SIZE * g_cameraPosX, tile.rc.top - TILE_SIZE * g_cameraPosY, to_string(referenceID).c_str(), (int)to_string(referenceID).size());
	}
}

void TriggerObj::Update()
{
}
