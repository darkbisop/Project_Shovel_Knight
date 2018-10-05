#include "stdafx.h"
#include "mainGame.h"
#include "ShopScene.h"
#include "playScene.h"

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

	setBackBuffer();

	m_ShopScene = new ShopScene;
	SCENEMANAGER->addScene("ShopScene", m_ShopScene);

	m_PlayScene = new PlayScene;
	SCENEMANAGER->addScene("PlayScene", m_PlayScene);

	SCENEMANAGER->changeScene("PlayScene");

	//m_ScreenAni->start();

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
	MAPMANAGER->release();
	PLAYER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();
	SOUNDMANAGER->releaseSingleton();
	MAPMANAGER->releaseSingleton();
	PLAYER->releaseSingleton();
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
