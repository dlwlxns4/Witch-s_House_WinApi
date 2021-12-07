#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X	00
#define WIN_START_POS_Y	0
#define WIN_SIZE_X	544
#define WIN_SIZE_Y	416
#define TILEMAPTOOL_SIZE_X	1500
#define TILEMAPTOOL_SIZE_Y	600
#define PI 3.14159265357989

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] p; p = nullptr; } }

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

enum class MoveDir { Left = 2, Right = 6, Up = 0, Down = 4 };
enum class TankType { Player, Normal, Speed, Rapid, Defensive };

#include "TimerManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TalkManager.h"
#include "UIManager.h"
#include "GameManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;


//콤보박스

//타일 관련
#define TILE_SIZE	32
#define TILE_COUNT_X	17
#define TILE_COUNT_Y	13
#define MAP_SIZE_X 100
#define MAP_SIZE_Y 100
#define LAYER_SIZE 3
#define SAMPLE_TILE_COUNT_X 5
#define SAMPLE_TILE_COUNT_Y	2

//버튼 관련
#define BTN_SIZE_X 144
#define BTN_SIZE_Y 60

//캐릭터 사이즈
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 48



enum class Terrain { Earth, Wall, Water, Grass, BreakableWall, End };

enum class TileType { Walkable, NoneWalkable };
typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	TileType tileType;
	RECT rc;				
	//image
	// sample tile의 아이디 (프레임 X, 프레임 Y)
	int frameX, frameY;
	int mapIndex;
	RECT collider;		// bullet Hit Collider
} TILE_INFO;