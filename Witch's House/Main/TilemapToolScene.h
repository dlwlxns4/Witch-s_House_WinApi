#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tilemap.h"
#include <filesystem>

enum class State{ NoneWalkable, Walkable  };

enum class TileState{ Tile=0, Playable=1, Trigger=2, Parallax=3, End=4 };

class Image;
class Button;
class Tile;
class Layer;
class TileObj;
class TriggerObj;
class TilemapToolScene : public GameEntity
{
private:

	//11-18�� ���� ���̾����� ������ �κ�
	TileObj* tileObj=nullptr;
	int currLayer = 0;
	int maxLayer = 1;
	
	
	//�����̹��� ���� (�巡�� ����)
	vector<pair<int, int>> selectPos = {};
	int startPosX = 0; // Ŭ�� ���� ����
	int startPosY = 0;


	//Tile tile[MAP_SIZE_X][MAP_SIZE_Y] = {};

	SAMPLE_TILE_INFO sampleTileInfo[30][30] = {};


	TILE_INFO tileInfo[MAP_SIZE_X][MAP_SIZE_Y] = {};
	Image* sampleImage = nullptr;

	SAMPLE_TILE_INFO	selectedSampleTile = {};

	vector<SAMPLE_TILE_INFO> selectedSampleTiles;

	int selectedIdX = 0, selectedIdY = 0;
	int posX = 0 , posY = 0;
	

	State state = {};
	TileType tileType = {};

	bool bShowNoneWalkable = false;
	bool bShowBodyCollider = false;

	char szText[256] = {};
	int mapIndex = 0;

	int SAMPLE_TILE_X = 0;
	int SAMPLE_TILE_Y = 0;


	Button* layerAddBtn;

	TileState tileState;

	//referenceID�� �����ϱ����� ������
	TriggerObj* TriggerObjForId;
	
public:
	virtual ~TilemapToolScene() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex=0);
	const string TileStateToString(TileState e);
	void Load(int loadIndex=0);
	TriggerObj* FindTriggerObj(int mousePosX, int mousePosY);
};

