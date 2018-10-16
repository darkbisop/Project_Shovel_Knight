#include "stdafx.h"
#include "bug.h"
#include "effectManager.h"

HRESULT bug::init(float x, float y)
{
	m_pImg_Move = IMAGEMANAGER->addImage("bug", "image/Enemy/bug/bug_move.bmp",
		104, 32, 4, 2, true, RGB(255, 0, 255));
	m_pImg_Die = IMAGEMANAGER->addImage("bug_Die", "image/Enemy/bug/bug_death.bmp",
		48, 34, 2, 2, true, RGB(255, 0, 255));
	m_nLife = 1;
	m_nPower = 1;
	m_fRange = 90.0f;
	m_fX = x;
	m_fY = y;
	m_rc = RectMakeCenter(m_fX, m_fY, m_pImg_Move->getFrameWidth(), m_pImg_Move->getFrameHeight());
	m_fSpeed = 0.5f;
	m_isAlive = true;
	m_isRight = false;
	m_isDying = false;
	m_isHitRight = false;

	// move상태
	m_nCurrFrameX_Move = 0;
	m_nCurrFrameY_Move = 0;
	m_nFrameCount_Move = 0;

	// die상태
	m_nCurrFrameX_Die = 0;
	m_nCurrFrameY_Die = 0;
	m_nFrameCount_Die = 0;
	m_nScalar = 1;

	m_fGravity = 0;
	m_fJumpSpeed = 3.0f;

	m_rcRange = RectMakeCenter(m_fX, m_fY, m_fRange, m_pImg_Move->getFrameHeight() * 2);	// 범위는 임의로 설정
	m_tempRc = RectMakeCenter(WINSIZEX / 2, 330, m_fRange, 20);

	EFFECTMANAGER->addEffect("bug_effect", "image/effect/enemy_effect.bmp", 120, 16, 24, 16, 10, 10);

	return S_OK;
}

void bug::release()
{
}

void bug::update()
{
	if (m_fX > PLAYER->getPlayerX()) {
		m_isHitRight = true;
	}
	if (m_fX < PLAYER->getPlayerX()) {
		m_isHitRight = false;
	}
	moveFrame();	// 움직일 때 프레임 카운트함수
	dieFrame();		// 죽을 때 프레임 카운트함수
	frameChange();	// 프레임 변경함수
	move();
	dieMove();
	//collide();
}

void bug::render(HDC hdc)
{

	if (m_isAlive)
	{
	/*	Rectangle(hdc, m_tempRc.left, m_tempRc.top, m_tempRc.right, m_tempRc.bottom);
		Rectangle(hdc, m_rcRange.left, m_rcRange.top, m_rcRange.right, m_rcRange.bottom);
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);*/
		if (!m_isDying)
		{
			m_pImg_Move->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Move, m_nCurrFrameY_Move);
		}
		else
		{
			m_pImg_Die->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Die, m_nCurrFrameY_Die);
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
		if (m_isHitRight == false)
		{
			m_fGravity += 0.2f;
			m_fX -= 1.0f;
			m_fY -= m_fJumpSpeed - m_fGravity;
			m_rc = RectMake(-1000, -1000, -1, -1);
		}
		else
		{
			m_fGravity += 0.2f;
			m_fX += 1.0f;
			m_fY -= m_fJumpSpeed - m_fGravity;
			m_rc = RectMake(-1000, -1000, -1, -1);
		}
	}
}


void bug::moveFrame()
{
	if (m_isAlive)
	{
		if (!m_isDying)
		{
			m_nFrameCount_Move++;
			if (m_nFrameCount_Move % 10 == 0)	// move상태 프레임카운트
			{
				m_nCurrFrameX_Move++;
				if (m_nCurrFrameX_Move > 4)
				{
					m_nCurrFrameX_Move = 0;
					m_nFrameCount_Move = 0;
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
			m_nFrameCount_Die++;
			if (m_nFrameCount_Die % 10 == 0)	// die상태 프레임 카운트
			{
				m_nCurrFrameX_Die++;
				if (m_nCurrFrameX_Die > 2)
				{
					m_nCurrFrameX_Die = 0;
					m_nFrameCount_Die = 0;

					EFFECTMANAGER->play("bug_effect", m_fX, m_fY);
					SOUNDMANAGER->play("버그다운킬", 1.0f);
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
			m_nCurrFrameY_Move = 0;
			if (m_isDying)
			{
				m_nCurrFrameY_Die = 0;
			}
		}
		if (!m_isRight)	// left상태 일 때 y프레임 변경
		{
			m_nCurrFrameY_Move = 1;
			if (m_isDying)
			{
				m_nCurrFrameY_Die = 1;
			}
		}
	}
}

void bug::collide()
{
	if (m_isAlive)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rc, &m_tempRc))
		{
			m_isAlive = false;
			EFFECTMANAGER->play("bug_effect", m_fX, m_fY);
		}
	}


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

void bug::Updamage(int damage)
{
	if (m_isAlive)
	{
		m_nLife -= damage;
		if (m_nLife == 0)
		{
			m_isAlive = false;
			EFFECTMANAGER->play("bug_effect", m_fX, m_fY);
			m_rc = RectMake(-1, -1, -1, -1);
		}
	}
}

bug::bug()
{
}


bug::~bug()
{
}
