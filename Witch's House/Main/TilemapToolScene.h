#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tilemap.h"
#include <filesystem>

enum class State{ NoneWalkable, Walkable  };

class Image;
class Button;
class Tile;
class Layer;
class TileObj;
class TilemapToolScene : public GameEntity
{
private:

	//11-18일 벡터 레이어으로 수정할 부분
	TileObj* tileObj=nullptr;
	int currLayer = 0;
	int maxLayer = 1;
	
	
	//Tile tile[MAP_SIZE_X][MAP_SIZE_Y] = {};

	SAMPLE_TILE_INFO sampleTileInfo[30][30] = {};


	TILE_INFO tileInfo[LAYER_SIZE][MAP_SIZE_X][MAP_SIZE_Y] = {};
	Image* sampleImage = nullptr;

	SAMPLE_TILE_INFO	selectedSampleTile = {};

	vector<SAMPLE_TILE_INFO> selectedSampleTiles;

	int selectedIdX = 0, selectedIdY = 0;
	int posX = 0 , posY = 0;
	
	int cameraX = 0;
	int cameraY = 0;

	State state = {};
	TileType tileType = {};

	bool bShowNoneWalkable = false;
	bool bShowBodyCollider = false;

	char szText[256] = {};
	int mapIndex = 0;

	int SAMPLE_TILE_X = 0;
	int SAMPLE_TILE_Y = 0;

	int currentLayer = 0;

	Button* layerAddBtn;
public:
	virtual ~TilemapToolScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex=0);
	void Load(int loadIndex=0);
};