#include "stdafx.h"
#include "tileMap.h"


HRESULT tileMap::init()
{
	m_pTileSet = IMAGEMANAGER->addImage("image/tileMap/maptiles.bmp",
		"image/tileMap/maptiles.bmp", 640, 288, 20, 9, true, RGB(255, 0, 255));

	 // 버튼 셋팅
	m_hBtnSave = CreateWindow("button", "Save",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WINSIZEX - m_pTileSet->getWidth(),
		m_pTileSet->getHeight() + 30, 100, 40,
		g_hWnd, HMENU(0), g_hInstance, NULL);

	m_hBtnLoad = CreateWindow("button", "Load",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WINSIZEX - m_pTileSet->getWidth() + 130,
		m_pTileSet->getHeight() + 30, 100, 40,
		g_hWnd, HMENU(0), g_hInstance, NULL);

	m_hBtnSelectTerrain = CreateWindow("button", "Terrain",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WINSIZEX - m_pTileSet->getWidth(),
		m_pTileSet->getHeight() + 80, 100, 40,
		g_hWnd, HMENU(0), g_hInstance, NULL);

	m_hBtnSelectObject = CreateWindow("button", "Object",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WINSIZEX - m_pTileSet->getWidth() + 130,
		m_pTileSet->getHeight() + 80, 100, 40,
		g_hWnd, HMENU(0), g_hInstance, NULL);

	m_hBtnEraser = CreateWindow("button", "Eraser",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WINSIZEX - m_pTileSet->getWidth() + 260,
		m_pTileSet->getHeight() + 80, 100, 40,
		g_hWnd, HMENU(0), g_hInstance, NULL);

	// 기본 타일 정보 셋팅
	for (int x = 0; x < TILE_X; x++)
	{
		for (int y = 0; y < TILE_Y; y++)
		{
			m_pTiles[x * TILE_X + y].rc = RectMake(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

			m_pTiles[x * TILE_X + y].terrainFrameX = 3;
			m_pTiles[x * TILE_X + y].terrainFrameY = 0;
		}
	}

	for (int y = 0; y < SAMPLE_TILE_Y; y++)
	{
		for (int x = 0; x < SAMPLE_TILE_X; x++)
		{
			m_pSampleTiles[y * SAMPLE_TILE_X + x].rc = RectMake(WINSIZEX - m_pTileSet->getWidth() 
				+ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

			m_pSampleTiles[y * SAMPLE_TILE_X + x].frameX = x;
			m_pSampleTiles[y * SAMPLE_TILE_X + x].frameY = y;
		}
	}

	TempX = 0;
	TempY = 0;

	return S_OK;
}

void tileMap::release()
{
}

void tileMap::update()
{
	for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++) {
	
		if (PtInRect(&m_pSampleTiles[i].rc, g_ptMouse)) {

			m_rcSelectedTile.left = m_pSampleTiles[i].frameX;
			m_rcSelectedTile.top = m_pSampleTiles[i].frameY;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				TempX = m_pSampleTiles[i].frameX;
				TempY = m_pSampleTiles[i].frameY;
			}
		}
	}

	for (int i = 0; i < TILE_X * TILE_Y; i++) {

		if (PtInRect(&m_pTiles[i].rc, g_ptMouse)) {

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				m_pTiles[i].terrainFrameX = TempX;
				m_pTiles[i].terrainFrameY = TempY;
			}
		}
	}
}


void tileMap::render(HDC hdc)
{
	if (m_pTileSet)
		m_pTileSet->render(hdc, WINSIZEX - m_pTileSet->getWidth(), 0);

	for (int x = 0; x < TILE_X; x++)
	{
		for (int y = 0; y < TILE_Y; y++)
		{
			m_pTileSet->frameRender(hdc, 
				m_pTiles[x * TILE_X + y].rc.left,
				m_pTiles[x * TILE_X + y].rc.top,
				m_pTiles[x * TILE_X + y].terrainFrameX,
				m_pTiles[x * TILE_X + y].terrainFrameY);
		}
	}

	// 선택 타일 표시
	m_pTileSet->frameRender(hdc,
		TILE_X * TILE_SIZE + 30,
		WINSIZEY / 2,
		m_rcSelectedTile.left,
		m_rcSelectedTile.top);
}

tileMap::tileMap()
	: m_pTileSet(NULL)
{
}


tileMap::~tileMap()
{
}
