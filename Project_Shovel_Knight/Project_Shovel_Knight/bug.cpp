#include "stdafx.h"
#include "bug.h"


HRESULT bug::init(float x, float y)
{
	m_pImg_Move = IMAGEMANAGER->addImage("bug", "image/enemy/bug/bug_move.bmp",
		104, 32, 4, 2, true, RGB(255, 0, 255));
	m_pImg_Die = IMAGEMANAGER->addImage("bug_Die", "image/enemy/bug/bug_death.bmp",
		48, 34, 2, 2, true, RGB(255, 0, 255));
	m_nLife = 1;
	m_nPower = 1;
	m_fRange = 80.0f;
	m_fX = x;
	m_fY = y;
	m_destX = m_fX;
	m_destY = m_fY;
	m_fRightAngle = 0.0f;// *PI / 180;
	m_fLeftAngle = 180.0f * PI / 180;
	m_rc = RectMakeCenter(m_fX, m_fY, m_pImg_Move->getFrameWidth(), m_pImg_Move->getFrameHeight());
	m_fSpeed = 0.5f;
	m_isAlive = true;
	m_isRight = false;
	m_isDying = false;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nFrameCount = 0;
	m_nDieFrameCount = 0;
	m_nDieFrameX = 0;
	m_nDieFrameY = 0;
	m_nScalar = 1;

	m_rcRange = RectMakeCenter(m_fX, m_fY, m_fRange, m_pImg_Move->getFrameHeight() * 2);	// 범위는 임의로 설정
	m_tempRc = RectMakeCenter(WINSIZEX / 2, 330, m_fRange, 20);
	
	
	return S_OK;
}

void bug::release()
{
}

void bug::update()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		damage(1);
	}
	
	moveFrame();	// 움직일 때 프레임 카운트함수
	dieFrame();		// 죽을 때 프레임 카운트함수
	frameChange();	// 프레임 변경함수
	move();
	dieMove();
	collide();
}

void bug::render(HDC hdc)
{
	Rectangle(hdc, m_tempRc.left, m_tempRc.top, m_tempRc.right, m_tempRc.bottom);
	Rectangle(hdc, m_rcRange.left, m_rcRange.top, m_rcRange.right, m_rcRange.bottom);
	if (m_isAlive)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (!m_isDying)
		{
			m_pImg_Move->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
		}
		else
		{
			m_pImg_Die->frameRender(hdc, m_fX, m_fY, m_nDieFrameX, m_nDieFrameY);
		}
	}
}

void bug::move()
{
	if (m_isAlive && !m_isDying)
	{
		if (m_rc.left < m_rcRange.left)
		{
			m_isRight = true;
		}
		if (m_rc.right > m_rcRange.right)
		{
			m_isRight = false;
		}
		//if (m_fX <= 0)
		//{
		//	m_isRight = true;
		//}
		//if (m_fX >= WINSIZEX - m_pImg_Move->getWidth()*2)
		//{
		//	m_isRight = false;
		//}
		if (m_isRight)
		{
			m_fX += m_fSpeed;
			m_fY += 0;
			m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
				m_pImg_Move->getFrameWidth() * m_nScalar, m_pImg_Move->getFrameHeight() * m_nScalar);
		}
		else if (!m_isRight)
		{
			m_fX -= m_fSpeed;
			m_fY += 0;
			m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
				m_pImg_Move->getFrameWidth() * m_nScalar, m_pImg_Move->getFrameHeight() * m_nScalar);
		}

	}
}

void bug::dieMove()
{
	if (m_isAlive && m_isDying)
	{
		if (m_isRight)	// 오른쪽방향상태에서 죽었을 때
		{
			m_fX = m_destX + cosf(m_fRightAngle) * 15.0f;
			m_fY = m_destY - sinf(m_fRightAngle) * 20.0f;
			m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar,
				m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
				m_pImg_Move->getFrameWidth() * m_nScalar, m_pImg_Move->getFrameHeight() * m_nScalar);
		}
		else if (!m_isRight)	// 왼쪽방향상태에서 죽었을 때
		{
			m_fX = m_destX + cosf(m_fLeftAngle) * 15.0f;
			m_fY = m_destY - sinf(m_fLeftAngle) * 20.0f;
			m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar,
				m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
				m_pImg_Move->getFrameWidth() * m_nScalar, m_pImg_Move->getFrameHeight() * m_nScalar);
		}
	}
}


void bug::moveFrame()
{
	if (m_isAlive)
	{
		if (!m_isDying)
		{
			m_nFrameCount++;
			if (m_nFrameCount % 10 == 0)	// move상태 프레임카운트
			{
				m_nCurrFrameX++;
				if (m_nCurrFrameX >= 4)
				{
					m_nCurrFrameX = 0;
					m_nFrameCount = 0;
				}
			}
		}
	}
}

void bug::dieFrame()
{
	if (m_isAlive)
	{
		if (m_isDying)
		{
			m_nDieFrameCount++;
			if (m_nDieFrameCount % 10 == 0)	// die상태 프레임 카운트
			{
				m_nDieFrameX++;
				if (m_nDieFrameX >= 4)
				{
					m_nDieFrameX = 0;
					m_nDieFrameCount = 0;

					m_rc = RectMake(-1000, -1000, -1, -1);
					EFFECTMANAGER->play("enemy_effect", m_fX, m_fY);
					m_isAlive = false;
				}
			}
		}
	}
}

void bug::frameChange()
{
	if (m_isAlive)
	{
		if (m_isRight)	//right상태 y프레임 변경
		{
			m_nCurrFrameY = 0;
			if (m_isDying)
			{
				m_nDieFrameY = 0;
				if (m_fRightAngle <= 180.0f * PI / 180)
				{
					m_fRightAngle += 0.1f;
				}
			}
		}
		if (!m_isRight)	// left상태 일 때 y프레임 변경
		{
			m_nCurrFrameY = 1;
			if (m_isDying)
			{
				m_nDieFrameY = 1;
				if (m_fLeftAngle >= 0.0f)
				{
					m_fLeftAngle -= 0.1f;
					if (m_fLeftAngle == 0.0f)
					{
						m_isAlive = false;
					}
				}
			}
		}
	}
}

void bug::collide()
{
	/*if (m_isAlive)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rc, &m_tempRc))
		{
			m_isAlive = false;
			m_pEffectMgr->play("enemy_effect", m_fX, m_fY);
		}
	}*/

	
}

void bug::damage(int damage)
{
	if (m_isAlive)
	{
		m_nLife -= damage;
		if (m_nLife == 0)
		{
			m_isDying = true;
		}
	}
}

bug::bug()
{
}


bug::~bug()
{
}
