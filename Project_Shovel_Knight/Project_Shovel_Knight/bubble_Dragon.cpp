#include "stdafx.h"
#include "bubble_Dragon.h"
#include "objectManager.h"
#include "effectManager.h"

bubble_Dragon::bubble_Dragon()
{
}


bubble_Dragon::~bubble_Dragon()
{
}

HRESULT bubble_Dragon::init(float x, float y)
{
	m_pImg_Idle = IMAGEMANAGER->addImage("bubble_Idle", "image/enemy/bubble_dragon/bubble_dragon_idle.bmp",
		2172, 88, 12, 1, true, RGB(255, 0, 255));
	m_pImg_Move = IMAGEMANAGER->addImage("bubble_Move", "image/enemy/bubble_dragon/bubble_dragon_move.bmp",
		1068, 89, 6, 1, true, RGB(255, 0, 255));
	m_pImg_Atk = IMAGEMANAGER->addImage("bubble_Atk", "image/enemy/bubble_dragon/bubble_dragon_Atk.bmp",
		1480, 83, 10, 1, true, RGB(255, 0, 255));
	m_pImg_Hit = IMAGEMANAGER->addImage("bubble_Hit", "image/enemy/bubble_dragon/bubble_dragon_damage.bmp",
		1068, 89, 6, 1, true, RGB(255, 0, 255));
	m_pImg_Die = IMAGEMANAGER->addImage("bubble_Die", "image/enemy/bubble_dragon/bubble_dragon_Die1.bmp",
		1480, 83, 10, 1, true, RGB(255, 0, 255));
	m_fX = x;
	m_fY = y;
	m_fSpeed = 0.5f;
	m_nLife = 1;
	m_isAlive = true;
	m_isDying = false;
	m_rc_Head = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2 + 15 - 50, m_fY + m_pImg_Idle->getFrameHeight() / 2 + 27, m_pImg_Idle->getFrameWidth() / 2 - 50, m_pImg_Idle->getFrameHeight() / 2 - 22);
	m_rc_Body = RectMakeCenter(m_fX + 125, m_fY + m_pImg_Idle->getFrameHeight() / 2 + 7, m_pImg_Idle->getFrameWidth() - 70, m_pImg_Idle->getFrameHeight() - 5);
	bubbleDG_state = BUBBLEDG_IDLE;
	m_pBubbleMgr = new objectManager;
	m_pBubbleMgr->init("image / enemy / bubble_dragon / bubble_move.bmp", 100.0f, 3);

	m_nFireCount = 0;

	// 이미지별 프레임 카운트	
	// idle
	m_nCurrFrameX_Idle = 0;
	m_nCurrFrameY_Idle = 0;
	m_nFrameCount_Idle = 0;

	// move
	m_nCurrFrameX_Move = 0;
	m_nCurrFrameY_Move = 0;
	m_nFrameCount_Move = 0;

	// atk
	m_nCurrFrameX_Atk = 0;
	m_nCurrFrameY_Atk = 0;
	m_nFrameCount_Atk = 0;

	// hit
	m_nCurrFrameX_Hit = 0;
	m_nCurrFrameY_Hit = 0;
	m_nFrameCount_Hit = 0;

	// die
	m_nCurrFrameX_Die = 0;
	m_nCurrFrameY_Die = 0;
	m_nFrameCount_Die = 0;

	EFFECTMANAGER->addEffect("effect", "image/effect/bubble_dragon_effect.bmp", 140, 29, 28, 29, 30, 1);
	m_nEffectCount = 0;
	return S_OK;
}

void bubble_Dragon::release()
{
	SAFE_DELETE(m_pBubbleMgr);
}

void bubble_Dragon::update()
{
	if (!m_isAlive)
	{
		if (m_pBubbleMgr)
		{
			m_pBubbleMgr->update();
		}
	}
	if (m_isAlive)
	{
		if (m_pBubbleMgr)
		{
			m_pBubbleMgr->update();
		}

		frameCount();
		move();
		fire();
		dieEffect();
	}
	m_pBubbleMgr->deleteBubble();
}

void bubble_Dragon::render(HDC hdc)
{
	if (m_isAlive)
	{
		Rectangle(hdc, m_rc_Head.left, m_rc_Head.top, m_rc_Head.right, m_rc_Head.bottom);
		Rectangle(hdc, m_rc_Body.left, m_rc_Body.top, m_rc_Body.right, m_rc_Body.bottom);
		if (bubbleDG_state == BUBBLEDG_IDLE)
		{
			m_pImg_Idle->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Idle, m_nCurrFrameY_Idle);
		}
		else if (bubbleDG_state == BUBBLEDG_MOVE)
		{
			m_pImg_Move->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Move, m_nCurrFrameY_Move);
		}
		else if (bubbleDG_state == BUBBLEDG_ATK)
		{
			m_pImg_Atk->frameRender(hdc, m_fX + 33, m_fY + 4, m_nCurrFrameX_Atk, m_nCurrFrameY_Atk);
		}
		else if (bubbleDG_state == BUBBLEDG_HIT)
		{
			m_pImg_Hit->frameRender(hdc, m_fX + 3, m_fY - 1, m_nCurrFrameX_Hit, m_nCurrFrameY_Hit);
		}
		else if (bubbleDG_state == BUBBLEDG_DIE)
		{
			m_pImg_Die->frameRender(hdc, m_fX + 33, m_fY + 5, m_nCurrFrameX_Die, m_nCurrFrameY_Die);
		}
		
		if (m_pBubbleMgr)
		{
			m_pBubbleMgr->render(hdc);
		}
	}
	if (!m_isAlive)
	{
		if (m_pBubbleMgr)
		{
			m_pBubbleMgr->render(hdc);
		}
	}

}

void bubble_Dragon::move()
{
	if (bubbleDG_state == BUBBLEDG_MOVE)
	{
		m_fX -= 0.1f;
		m_rc_Head = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2 + 15 - 50, m_fY + m_pImg_Idle->getFrameHeight() / 2 + 27, m_pImg_Idle->getFrameWidth() / 2 - 50, m_pImg_Idle->getFrameHeight() / 2 - 22);
		m_rc_Body = RectMakeCenter(m_fX + 125, m_fY + m_pImg_Idle->getFrameHeight() / 2 + 7, m_pImg_Idle->getFrameWidth() - 70, m_pImg_Idle->getFrameHeight() - 5);
	}
}

void bubble_Dragon::damage(int damage)
{
	m_nLife -= damage;
	bubbleDG_state = BUBBLEDG_HIT;
	if (m_nLife == 0)
	{
		bubbleDG_state = BUBBLEDG_DIE;
		//m_isAlive = false;
	}

}

void bubble_Dragon::fire()
{
	if (m_isAlive)
	{
		if (m_nCurrFrameX_Atk > 3 && bubbleDG_state == BUBBLEDG_ATK)
		{
			m_nFireCount++;
			if (m_nFireCount % 35 == 0)
			{
				m_pBubbleMgr->fire(m_fX + 10, m_fY + 55, 180.0f * PI / 180, 2.0f);
				m_nFireCount = 0;
			}
		}
	}


}

void bubble_Dragon::frameCount()
{
	if (bubbleDG_state == BUBBLEDG_IDLE)
	{
		m_nFrameCount_Idle++;
		if (m_nFrameCount_Idle % 10 == 0)
		{
			m_nCurrFrameX_Idle++;
			if (m_nCurrFrameX_Idle > 12)
			{
				bubbleDG_state = BUBBLEDG_ATK;
				m_nCurrFrameX_Hit = 0;
				//m_nCurrFrameX_Idle = 0;
				m_nFrameCount_Idle = 0;
			}
		}
	}
	if (bubbleDG_state == BUBBLEDG_MOVE)
	{
		m_nFrameCount_Move++;
		if (m_nFrameCount_Move % 10 == 0)
		{
			m_nCurrFrameX_Move++;
			if (m_nCurrFrameX_Move > 6)
			{
				bubbleDG_state = BUBBLEDG_IDLE;
				m_nCurrFrameX_Atk = 0;
				m_nCurrFrameX_Idle = 0;
				//m_nCurrFrameX_Move = 0;
				m_nFrameCount_Move = 0;
			}
		}
	}
	if (bubbleDG_state == BUBBLEDG_ATK)
	{
		m_nFrameCount_Atk++;
		if (m_nFrameCount_Atk % 16 == 0)
		{
			m_nCurrFrameX_Atk++;
			if (m_nCurrFrameX_Atk > 10)
			{
				bubbleDG_state = BUBBLEDG_MOVE;
				m_nCurrFrameX_Move = 0;
				//m_nCurrFrameX_Atk = 0;
				m_nFrameCount_Atk = 0;
			}
		}
	}
	if (bubbleDG_state == BUBBLEDG_HIT)
	{
		m_nFrameCount_Hit++;
		if (m_nFrameCount_Hit % 4 == 0)
		{
			m_nCurrFrameX_Hit++;
			if (m_nCurrFrameX_Hit > 6)
			{
				bubbleDG_state = BUBBLEDG_IDLE;
				m_nFrameCount_Hit = 0;
			}
		}
	}
	if (bubbleDG_state == BUBBLEDG_DIE)
	{
		m_nFrameCount_Die++;
		if (m_nFrameCount_Die % 10 == 0)
		{
			m_nCurrFrameX_Die++;
			if (m_nCurrFrameX_Die > 10)
			{
				m_nCurrFrameX_Die = 0;
				m_nFrameCount_Die = 0;

				m_rc_Head = RectMakeCenter(-1, -1, -1, -1);
				m_rc_Body = RectMakeCenter(-1, -1, -1, -1);
			}
		}
	}


}

void bubble_Dragon::dieEffect()
{
	if (bubbleDG_state == BUBBLEDG_DIE)
	{
		EFFECTMANAGER->play("effect", RANDOM->getFromFloatTo(m_rc_Head.left, m_rc_Body.right), RANDOM->getFromFloatTo(m_rc_Head.top - 80, m_rc_Body.bottom));
		m_nEffectCount++;
		if (m_nEffectCount > 120)
		{
			m_isAlive = false;
		}
	}
}
