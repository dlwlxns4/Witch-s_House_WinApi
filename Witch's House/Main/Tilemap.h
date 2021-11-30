#pragma once
#include "Image.h"
#include <vector>
#include <string>
#include "Layer.h"
#include "TileObj.h"
#include "PlayerObj.h"
#include "ParallaxObj.h"
#include "TriggerObj.h"

//�� �ε���
extern vector<Image*> vecSampleImage;
extern vector<Image*> vecLayerBtnImage;

//���� ���
extern vector<string> mapName;
extern vector<string> btnName;

//Ÿ�ϸ� �ε���
extern bool g_isBtnActive;


extern vector<Layer*> vecLayer;
extern vector<TileObj*> vecTileObj;
extern PlayerObj* playerObj;
extern ParallaxObj* parallaxObj;
extern TriggerObj* triggerObj;

//TriggerObj �� refereceID���� �ֱ� ���� vector
extern vector<TriggerObj*> vecTriggerObj;