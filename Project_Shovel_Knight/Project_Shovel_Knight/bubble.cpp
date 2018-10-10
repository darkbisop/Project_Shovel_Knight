#include "stdafx.h"
#include "bubble.h"


HRESULT bubble::init()
{
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fFiredX = 0;
	m_fFiredY = 0;
	m_fSpeed = 5.0f;
	m_fAngle = 0.0f;
	m_fRange = 0.0f;
	m_isFire = false;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;
	m_nBubbleCount = 0;
	ZeroMemory(&m_rc, sizeof(m_rc));
	m_pImg = IMAGEMANAGER->addImage("bubble", "image/enemy/bubble_dragon/bubble_move.bmp",
		108, 27, 4, 1, true, RGB(255, 0, 255));
	//m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	return S_OK;
}

HRESULT bubble::init(const char * szImageName, float speed, float x, float y, float angle, float range)
{
	m_fX = x;
	m_fY = y;
	m_fFiredX = x;
	m_fFiredY = y;
	m_fRange = range;
	m_fAngle = angle;
	m_fSpeed = speed;
	m_isFire = false;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;
	m_nBubbleCount = 0;
	ZeroMemory(&m_rc, sizeof(m_rc));
	m_pImg = IMAGEMANAGER->addImage("bubble", "image/enemy/bubble_dragon/bubble_move.bmp",
		108, 27, 4, 1, true, RGB(255, 0, 255));
	//m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
	return S_OK;
}

void bubble::release()
{
}

void bubble::update()
{
	move();
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
}

void bubble::render(HDC hdc)
{
	if (m_isFire)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		m_pImg->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
	}
}

void bubble::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;

		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;

		m_rc = RectMakeCenter(m_fX + m_pImg->getFrameWidth() / 2, m_fY + m_pImg->getFrameHeight() / 2, 20, 20);
	}
}

void bubble::move()
{
	if (m_isFire)
	{
		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY -= 0.0f;
		m_rc = RectMakeCenter(m_fX + m_pImg->getFrameWidth() / 2, m_fY + m_pImg->getFrameHeight() / 2, m_pImg->getFrameWidth(),
			m_pImg->getFrameHeight());
		if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
		{
			m_fX += cosf(0)* m_fSpeed;
			m_fY -= sinf(90 * PI / 180) * 0.3f;
			m_rc = RectMakeCenter(m_fX + m_pImg->getFrameWidth() / 2, m_fY + m_pImg->getFrameHeight() / 2, 20, 20);
		}
		/*if (m_fX < 10 || m_fY < 10)
		{
			m_isFire = false;
		}*/
	}
}

bubble::bubble()
{
}


bubble::~bubble()
{
}
