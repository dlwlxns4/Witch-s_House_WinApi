#pragma once
#include "Image.h"
#include <vector>
#include <string>
#include "Layer.h"
#include "TileObj.h"
#include "PlayerObj.h"


//∏  ¿Œµ¶Ω∫
extern vector<Image*> vecSampleImage;
extern vector<Image*> vecLayerBtnImage;

//∆ƒ¿œ ∞Ê∑Œ
extern vector<string> mapName;
extern vector<string> btnName;

//≈∏¿œ∏  ¿Œµ¶Ω∫
extern bool g_isBtnActive;


extern vector<Layer*> vecLayer;
extern vector<TileObj*> vecTileObj;
extern PlayerObj* playerObj;