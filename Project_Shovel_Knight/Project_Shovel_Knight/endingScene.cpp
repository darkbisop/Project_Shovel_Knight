#include "stdafx.h"
#include "endingScene.h"


HRESULT endingScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("endingScene", "image/Title/ending_Scene.bmp", 24400, 208, 61, 1, true, RGB(255, 0, 255));

	m_pGameOver = IMAGEMANAGER->addImage("gameOver", "image/Title/gameover.bmp", 400, 208, false, RGB(255, 0, 255));
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;
	m_nAlphaCount = 0;
	m_isPrintOver = false;

	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	m_nFrameCount++;
	if (m_nFrameCount % 4 == 0)
	{
		m_nCurrFrameX++;
		if (m_nCurrFrameX > 61)
		{
			m_nCurrFrameX = 61;
			m_nFrameCount = 0;
			m_isPrintOver = true;
		}
	}
	if (m_isPrintOver)
	{
		m_nAlphaCount++;
		if (m_nAlphaCount >= 255)
		{
			m_nAlphaCount = 255;
		}
	}
	
}

void endingScene::render(HDC hdc)
{
	m_pBG->frameRender(hdc, 0, 0, m_nCurrFrameX, m_nCurrFrameY);
	if (m_isPrintOver) m_pGameOver->alphaRender(hdc, 0, 0, m_nAlphaCount);	
	//else
	//char str[64];
	//sprintf_s(str, "D : %d", m_nAlphaCount);
	//TextOut(hdc, 100, 100, str, strlen(str));
}

endingScene::endingScene()
{
}


endingScene::~endingScene()
{
}
