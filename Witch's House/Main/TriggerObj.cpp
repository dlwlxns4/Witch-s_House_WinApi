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
		tile.rc.left + TILE_SIZE / 2 - TILE_SIZE - TILE_SIZE * g_cameraPosX,
		tile.rc.top + TILE_SIZE / 2 - TILE_SIZE - TILE_SIZE * g_cameraPosY,
		tile.frameX,
		tile.frameY
	);


	TextOut(hdc, tile.rc.left-32 - TILE_SIZE * g_cameraPosX, tile.rc.top-32 - TILE_SIZE * g_cameraPosY, to_string(referenceID).c_str(), to_string(referenceID).size());
}

void TriggerObj::Update()
{
}
