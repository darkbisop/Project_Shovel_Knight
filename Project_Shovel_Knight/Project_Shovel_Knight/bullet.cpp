#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init()
{
	m_pImg = IMAGEMANAGER->addImage("bullet", "image/boss/black_knight/atk/black_knight_bullet.bmp", 140, 40, 4, 2, true, RGB(255, 0, 255));
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fSpeed = 0.0f;
	m_fFiredX = 0.0f;
	m_fFiredY = 0.0f;
	m_fAngle = 0.0f;
	m_fRange = 100.0f;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;
	m_isFire = false;

	ZeroMemory(&m_rc, sizeof(m_rc));

	return S_OK;
}

HRESULT bullet::init(const char * szImageName, float speed, float x, float y, float angle, float range, int currFrameY)
{
	m_pImg = IMAGEMANAGER->addImage("bullet", "image/boss/black_knight/atk/black_knight_bullet.bmp", 140, 40, 4, 2, true, RGB(255, 0, 255));
	m_fX = x;
	m_fY = y;
	m_fSpeed = speed;
	m_fFiredX = x;
	m_fFiredY = y;
	m_fAngle = angle;
	m_fRange = range;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = currFrameY;
	m_nFrameCount = 0;
	m_isFire = false;

	ZeroMemory(&m_rc, sizeof(m_rc));
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	m_nFrameCount++;
	if (m_nFrameCount % 10 == 0)
	{
		m_nCurrFrameX++;
		if (m_nCurrFrameX > 4)
		{
			m_nCurrFrameX = 0;
			m_nFrameCount = 0;
		}
	}
	move();
}

void bullet::render(HDC hdc)
{
	if (m_isFire)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		m_pImg->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
	}
}

void bullet::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;

		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;

		m_rc = RectMakeCenter(m_fX + m_pImg->getFrameWidth() / 2, m_fY + m_pImg->getFrameHeight() / 2, m_pImg->getFrameWidth(),
			m_pImg->getFrameHeight());
	}
}

void bullet::move()
{
	if (m_isFire)
	{
		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY -= 0;
		m_rc = RectMakeCenter(m_fX + m_pImg->getFrameWidth() / 2, m_fY + m_pImg->getFrameHeight() / 2, m_pImg->getFrameWidth(),
			m_pImg->getFrameHeight());
		if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
		{
			m_isFire = false;
		}
	}
}
