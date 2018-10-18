#include "stdafx.h"
#include "mainGame.h"
#include "playScene.h"
#include "titleScene.h"
#include "TestScene.h"
#include "endingScene.h"

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();
	SOUNDMANAGER->init();
	EFFECTMANAGER->init();

	setBackBuffer();

	m_TestScene = new TestScene;
	SCENEMANAGER->addScene("TestScene", m_TestScene);

	m_titleScene = new titleScene;
	SCENEMANAGER->addScene("titleScene", m_titleScene);

	m_PlayScene = new PlayScene;
	SCENEMANAGER->addScene("PlayScene", m_PlayScene);

	m_endingScene = new endingScene;
	SCENEMANAGER->addScene("endingScene", m_endingScene);

	SCENEMANAGER->changeScene("TestScene");

	return S_OK;
}

void mainGame::release()
{
	SAFE_DELETE(m_pBackBuffer);

	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();
	SOUNDMANAGER->release();
	EFFECTMANAGER->release();
	MAPMANAGER->release();
	PLAYER->release();
	ENEMYMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();
	SOUNDMANAGER->releaseSingleton();
	EFFECTMANAGER->releaseSingleton();
	MAPMANAGER->releaseSingleton();
	PLAYER->releaseSingleton();
	ENEMYMANAGER->releaseSingleton();
}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{
	InvalidateRect(g_hWnd, NULL, false);

	SCENEMANAGER->update();
	SOUNDMANAGER->update();
	//m_ScreenAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();

	SCENEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0, WINSIZEX * WINDOW_ZOOM_RATE, WINSIZEY * WINDOW_ZOOM_RATE);
}

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
