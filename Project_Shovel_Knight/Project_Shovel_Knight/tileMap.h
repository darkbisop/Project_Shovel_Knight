#pragma once
#include "scene.h"

#define TILE_SIZE	32

#define TILE_X	20
#define TILE_Y	20

#define SAMPLE_TILE_X	20
#define SAMPLE_TILE_Y	9

enum TERRAIN
{
	TR_GRASS, TR_WATER, TR_EARTH, TR_CEMENT, TR_NUM
};

enum OBJECT
{
	OBJ_BLOCK_1, OBJ_BLOCK_2, OBJ_FLAG_RED, OBJ_FLAG_BLUE,
	OBJ_BUSH_1, OBJ_BUSH_2, OBJ_ROCK_SMALL, OBJ_ROCK_BIG, OBJ_NUM
};


struct tagTile
{
	TERRAIN terrain;
	OBJECT object;

	int terrainFrameX;	// Ÿ���� ������ �ִ� ��������
	int terrainFrameY;

	int objectFrameX;	// Ÿ���� ������ �ִ� ��������
	int objectFrameY;

	RECT	rc;
};

struct tagSampleTile
{
	RECT rc;
	int frameX;
	int frameY;
};

class tileMap : public scene
{
private:
	HWND	m_hBtnSave;
	HWND	m_hBtnLoad;
	HWND	m_hBtnSelectTerrain; // ������ �����ϴ� ��ư
	HWND	m_hBtnSelectObject;
	HWND	m_hBtnEraser;

	image*	m_pTileSet; // Ÿ���� ��Ƴ��� �̹���

	tagTile m_pTiles[TILE_X * TILE_Y];
	tagSampleTile	m_pSampleTiles[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT	m_rcSelectedTile;
	int TempX;
	int TempY;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	tileMap();
	~tileMap();
};

