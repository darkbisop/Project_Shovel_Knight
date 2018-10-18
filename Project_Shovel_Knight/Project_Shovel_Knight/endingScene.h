#pragma once
#include "scene.h"
class endingScene : public scene
{
private:
	image*	m_pBG;
	image*	m_pGameOver;
	
	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nFrameCount;

	int		m_nAlphaCount;

	bool	m_isPrintOver;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	endingScene();
	~endingScene();
};

