#include "stdafx.h"
#include "BubleBuble.h"


HRESULT BubleBuble::init(float x, float y, float rangeY, bool up)
{
	m_img = IMAGEMANAGER->addImage("bubble", "image/Enemy/bubble_dragon/bubble_move.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	
	m_fX = x;
	m_fY = y;

	m_fSpeed = 0.7f;
	nFrameCount = 0;
	_rc = RectMakeCenter(m_fX, m_fY, 20, 20);
	m_rangeRC = RectMakeCenter(m_fX, m_fY, 20, rangeY);

	m_isUp = up;

	_isAlive = true;

	return S_OK;
}

void BubleBuble::release()
{
}

void BubleBuble::update()
{
	nFrameCount++;
	if (nFrameCount % 8 == 0)
	{
		m_nCurrFrameX++;
		if (m_nCurrFrameX > 4)
		{
			m_nCurrFrameX = 0;
			nFrameCount = 0;
		}
	}

	if (_rc.bottom > m_rangeRC.bottom) {
		m_isUp = true;
	}
	else if (_rc.top < m_rangeRC.top) {
		m_isUp = false;
	}

	if (_isAlive) {
		if (m_isUp) {
			m_fX += 0;
			m_fY -= m_fSpeed;
			_rc = RectMakeCenter(m_fX, m_fY, 20, 20);
		}
	}
	else _rc = RectMakeCenter(-1,-1, -1, -1);
}

void BubleBuble::render(HDC hdc)
{
	if (_isAlive) {
		Rectangle(hdc, m_rangeRC.left, m_rangeRC.top, m_rangeRC.right, m_rangeRC.bottom);
		m_img->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, 0);
	}
}

BubleBuble::BubleBuble()
{
}


BubleBuble::~BubleBuble()
{
}
