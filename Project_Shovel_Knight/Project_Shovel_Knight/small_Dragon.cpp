#include "stdafx.h"
#include "small_Dragon.h"

HRESULT small_Dragon::init(float x, float y, smallDG_State phase)
{
	m_pImg_Move = IMAGEMANAGER->addImage("smallDG", "image/Enemy/small_dragon/small_dragon_idle.bmp",
		102, 64, 3, 2, true, RGB(255, 0, 255));
	m_pImg_HitR = IMAGEMANAGER->addImage("smallDG_HitR", "image/Enemy/small_dragon/small_dragon_hit(R).bmp", 34, 34, true, RGB(255, 0, 255));
	m_pImg_HitL = IMAGEMANAGER->addImage("smallDG_HitL", "image/Enemy/small_dragon/small_dragon_hit(L).bmp", 34, 34, true, RGB(255, 0, 255));
	m_fX = x;
	m_fY = y;
	m_destX = m_fX;
	m_destY = m_fY;
	m_rc = RectMakeCenter(m_fX, m_fY, m_pImg_Move->getFrameWidth(), m_pImg_Move->getFrameHeight());
	m_fSpeed = 1.0f;
	m_nCurrFrameX_Move = 0;
	m_nCurrFrameY_Move = 0;
	m_nLife = 2;
	m_nPower = 1;
	m_nFrameCount_Move = 0;
	m_nScalar = 1;
	m_isAlive = true;
	m_isDamage = false;	// 피격 당했을 때
	m_nDamageCount = 0;

	// 범위 Rect
	m_rcUpDownRange = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2, m_fY, m_pImg_Move->getFrameWidth(), 100);
	m_rcStraightRange = RectMakeCenter(m_fX, m_fY + m_pImg_Move->getFrameHeight() / 2, 500, m_pImg_Move->getFrameWidth());

	// 움직임 1에 필요한 변수
	m_fRightAngle = 180.0f * PI / 180;
	m_fLeftAngle = 360.0f * PI / 180;

	// 움직임 패턴을 위한 변수
	m_pSmallDG_State = phase;
	m_isRight = false;
	m_isUp = true;

	EFFECTMANAGER->addEffect("smallDG_effect", "image/effect/enemy_effect.bmp", 120, 16, 24, 16, 10, 10);

	return S_OK;
}

void small_Dragon::release()
{
}

void small_Dragon::update()
{
	m_nDamageCount++;
	if (m_nDamageCount % 30 == 0)	// hit이미지를 깜빡이게 하기위한 식
	{
		m_isDamage = false;
		m_nDamageCount = 0;
	}
	m_nFrameCount_Move++;
	if (m_nFrameCount_Move % 8 == 0)		// 프레임카운트
	{
		m_nCurrFrameX_Move++;
		if (m_nCurrFrameX_Move > 3)
		{
			m_nCurrFrameX_Move = 0;
			m_nFrameCount_Move = 0;
		}
	}
	
	move();
}

void small_Dragon::render(HDC hdc)
{
	if (m_isAlive)
	{
		if (m_pSmallDG_State == smallDG_UPDOWN)
		{
			//Rectangle(hdc, m_rcUpDownRange.left, m_rcUpDownRange.top, m_rcUpDownRange.right, m_rcUpDownRange.bottom);
		}
		if (m_pSmallDG_State == smallDG_STRAIGHT)
		{
			//Rectangle(hdc, m_rcStraightRange.left, m_rcStraightRange.top, m_rcStraightRange.right, m_rcStraightRange.bottom);
		}
		if (!m_isDamage)
		{
			if (m_pSmallDG_State == smallDG_CIRCLE)
			{
				Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
				m_pImg_Move->frameRender(hdc, m_fX, m_fY,
					m_nCurrFrameX_Move, m_nCurrFrameY_Move);
			}
			if (m_pSmallDG_State == smallDG_STRAIGHT)
			{
				Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
				if (m_isRight)
				{
					m_pImg_Move->frameRender(hdc, m_fX, m_fY,
						m_nCurrFrameX_Move, m_nCurrFrameY_Move);
				}
				else
				{
					m_pImg_Move->frameRender(hdc, m_fX, m_fY,
						m_nCurrFrameX_Move, m_nCurrFrameY_Move);
				}
			}
			if (m_pSmallDG_State == smallDG_UPDOWN)
			{
				Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
				if (m_isRight)
				{
					m_pImg_Move->frameRender(hdc, m_fX, m_fY,
						m_nCurrFrameX_Move, m_nCurrFrameY_Move);
				}
				else
				{
					m_pImg_Move->frameRender(hdc, m_fX, m_fY,
						m_nCurrFrameX_Move, 1);
				}
			}
		}
		else
		{
			if (m_isRight)
			{
				m_pImg_HitR->hitRender(hdc, m_fX, m_fY, RGB(255, 0, 0));
			}
			else
			{
				m_pImg_HitL->hitRender(hdc, m_fX, m_fY, RGB(255, 0, 0));
			}
		}
	}

	//char str[64];
	//wsprintf(str, "%d", m_nLife);
	////sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	//TextOut(hdc, m_fX, m_fY, str, strlen(str));
}

void small_Dragon::move()
{
	if (m_isAlive)
	{
		if (m_pSmallDG_State == smallDG_STRAIGHT)	// 게임 상에서 왼쪽으로 만 이동
		{
			if (m_fX <= m_rcStraightRange.left)	// 정해진 범위 넘어가면 사라지게
			{
				//m_isRight = true;
				//m_nCurrFrameY = 0;
				m_isAlive = false;
			}
			if (m_rc.right >= m_rcStraightRange.right)
			{
				m_isRight = false;
			}
			//if (m_isRight)
			//{
			//	m_fX += m_fSpeed;
			//	m_fY += 0;
			//	m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
			//		m_pImg_Move->getFrameWidth() * m_nScalar, m_pImg_Move->getFrameHeight() * m_nScalar);
			//}
			if (!m_isRight)
			{
				m_nCurrFrameY_Move = 1;
				m_fX -= m_fSpeed;
				m_fY += 0;
				m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
					20, 20);
			}
		}
		if (m_pSmallDG_State == smallDG_UPDOWN)
		{
			if (m_fY < m_rcUpDownRange.top)	// 위아래 움직이게 구현 할 조건
			{
				m_isUp = false;
			}
			if (m_rc.bottom > m_rcUpDownRange.bottom)
			{
				m_isUp = true;
			}
			if (m_fX < PLAYER->getPlayerX())	// 플레이어 x 위치에 따른 프레임 변화
			{
				m_isRight = true;
			}
			if (m_fX > PLAYER->getPlayerX())
			{ 
				m_isRight = false;
			}
			if (m_isUp)
			{
				m_fX -= 0;
				m_fY -= m_fSpeed;
				m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
					20, 20);
				if (m_isRight)
				{
					m_nCurrFrameY_Move = 0;
				}
				if (!m_isRight)
				{
					m_nCurrFrameY_Move = 1;
				}
			}
			else if (!m_isUp)
			{
				m_fX -= 0;
				m_fY += m_fSpeed;
				m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
					20, 20);
				if (m_isRight)
				{
					m_nCurrFrameY_Move = 0;
				}
				if (!m_isRight)
				{
					m_nCurrFrameY_Move = 1;
				}
			}
		}
		else if (m_pSmallDG_State == smallDG_CIRCLE)
		{
			if (m_fRightAngle < 0.0f)
			{
				m_isRight = false;
				m_fRightAngle = 180.0f * PI / 180;
			}
			if (m_fLeftAngle < 180.0f * PI / 180)
			{
				m_isRight = true;
				m_fLeftAngle = 360.0f * PI / 180;
			}
			if (m_isRight)	//right상태 y프레임 변경
			{
				m_nCurrFrameY_Move = 0;
				m_fRightAngle -= 0.01f;
			}
			if (!m_isRight)	//right상태 y프레임 변경
			{
				m_nCurrFrameY_Move = 1;
				m_fLeftAngle -= 0.01f;
			}
			if (m_isRight)
			{
				m_fX = m_destX + cosf(m_fRightAngle) * 25.0f;
				m_fY = m_destY - sinf(m_fRightAngle) * 10.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
					20, 20);
			}
			if (!m_isRight)
			{
				m_fX = m_destX + cosf(m_fLeftAngle) * 25.0f;
				m_fY = m_destY - sinf(m_fLeftAngle) * 10.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Move->getFrameWidth() / 2 * m_nScalar, m_fY + m_pImg_Move->getFrameHeight() / 2 * m_nScalar,
					20, 20);
			}
		}
		
	}
}

void small_Dragon::damage(int damage)
{
	if (m_isAlive)
	{
		m_nLife -= damage;
		m_isDamage = true;
	
		if (m_nLife == 0)
		{
			EFFECTMANAGER->play("smallDG_effect", m_fX, m_fY);
			m_isAlive = false;
			m_rc = RectMakeCenter(-1, -1, -1, -1);
			// 이펙트 출력
		}	

	}
}

small_Dragon::small_Dragon()
{
}


small_Dragon::~small_Dragon()
{
}
