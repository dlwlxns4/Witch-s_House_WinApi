#pragma once
#include "Image.h"
#include <vector>
#include <string>
#include "Layer.h"
#include "TileObj.h"
#include "PlayerObj.h"
#include "ParallaxObj.h"
#include "TriggerObj.h"

//맵 인덱스
extern vector<Image*> vecSampleImage;
extern vector<Image*> vecLayerBtnImage;

//파일 경로
extern vector<string> mapName;
extern vector<string> btnName;

//타일맵 인덱스
extern bool g_isBtnActive;


extern vector<Layer*> vecLayer;
extern vector<TileObj*> vecTileObj;
extern PlayerObj* playerObj;
extern ParallaxObj* parallaxObj;
extern TriggerObj* triggerObj;

//TriggerObj 에 refereceID값을 주기 위한 vector
extern vector<TriggerObj*> vecTriggerObj;