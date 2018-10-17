#include "stdafx.h"
#include "black_Knight.h"
#include "bulletManager.h"
#include "spaceShip.h"

black_Knight::black_Knight()
{
}


black_Knight::~black_Knight()
{
}

HRESULT black_Knight::init(float x, float y)
{
	initImg();	// 이미지 파일 초기화 함수

	m_fX = x;
	m_fY = y;

	m_fRange = 100;
	m_fSpeed = 1.0f;
	m_fAngle = 0.0f;

	m_isAlive = true;
	m_isRight = false;
	m_isDying = false;
	m_isAtk = false;
	m_isJump = false;
	m_isDamage = false;
	m_isFire = false;

	m_nLife = 12;
	m_nFireCount = 0;
	m_nEventIdleCount = 0;
	m_fGravity = 0;
	m_fJumpSpeed = 7.0f;
	m_fBackStepSpeed = 3.0f;

	m_pBulletMgr = new bulletManager;
	m_pBulletMgr->init("image/boss/black_knight/atk/black_knight_bullet.bmp",1000,3);

	m_fDieJumpSpeed = 5.0f;
	m_nDamageTime = 0;
	m_fDamageJumpSpeed = 5.0f;

	if (m_isRight)
	{
		m_nCurrFrameX_Idle = 0;
		m_nCurrFrameY_Idle = 0;
		m_nFrameCount_Idle = 0;

		m_nCurrFrameX_eventIdle = 0;
		m_nCurrFrameY_eventIdle = 0;
		m_nFrameCount_eventIdle = 0;

		m_nCurrFrameX_Move = 0;
		m_nCurrFrameY_Move = 0;
		m_nFrameCount_Move = 0;

		m_nCurrFrameX_basicAtk = 0;
		m_nCurrFrameY_basicAtk = 0;
		m_nFrameCount_basicAtk = 0;
	}
	if (!m_isRight)
	{
		m_nCurrFrameX_Idle = 2;
		m_nCurrFrameY_Idle = 1;
		m_nFrameCount_Idle = 0;

		m_nCurrFrameX_eventIdle = 2;
		m_nCurrFrameY_eventIdle = 1;
		m_nFrameCount_eventIdle = 0;

		m_nCurrFrameX_Move = 6;
		m_nCurrFrameY_Move = 1;
		m_nFrameCount_Move = 0;

		m_nCurrFrameX_basicAtk = 4;
		m_nCurrFrameY_basicAtk = 1;
		m_nFrameCount_basicAtk = 0;
	}

	m_nCurrFrameX_jumpAtk2 = 0;
	m_nCurrFrameY_jumpAtk2 = 0;
	m_nFrameCount_jumpAtk2 = 0;

	m_nCurrFrameX_shootAtk1 = 0;
	m_nCurrFrameY_shootAtk1 = 0;
	m_nFrameCount_shootAtk1 = 0;

	m_nCurrFrameX_Die = 0;
	m_nCurrFrameY_Die = 0;
	m_nFrameCount_Die = 0;

	m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2, m_fY + m_pImg_Idle->getFrameHeight() / 2, m_pImg_Idle->getFrameWidth(), m_pImg_Idle->getFrameHeight());
	m_rcRange = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2, m_fY + m_pImg_Idle->getFrameHeight() / 2, m_fRange + 300, 50);
	m_rcTemp = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2, m_fY + m_pImg_Idle->getFrameHeight() / 2 + 50, m_fRange + 300, 50);

	m_nBossState = BOSS_IDLE;	// 보스 현재 상태

	m_nAtkCount = 0;		// 기본 공격 시 렉트 생성 카운트
	m_nMoveCount = 0;		// 무브 카운트
	m_nBasicAtkCount = 0;	// 기본 공격 카운트
	m_nShootAtkCount = 0;	// 슈팅 공격 카운트
	m_nJumpAtkCount = 0;	// 점프 공격 카운트

	// 보스 체력 위치
	m_fX_Hp = MAPMANAGER->getCamera().x + 388;
	m_fY_Hp = MAPMANAGER->getCamera().y + 9;

	return S_OK;
}

void black_Knight::initImg()
{
	// 보스 상태 별 이미지 초기화
	m_pImg_Idle = IMAGEMANAGER->addImage("idle", "image/boss/black_knight/idle/black_knight_startidle.bmp", 44, 72, 2, 2, true, RGB(255, 0, 255));
	m_pImg_eventIdle = IMAGEMANAGER->addImage("eventidle", "image/boss/black_knight/idle/black_knight_event_idle.bmp", 65, 35, 2, 1, true, RGB(255, 0, 255));
	m_pImg_Move = IMAGEMANAGER->addImage("move", "image/boss/black_knight/move/black_knight_move.bmp", 198, 74, 6, 2, true, RGB(255, 0, 255));
	m_pImg_backStepL = IMAGEMANAGER->addImage("backStepL", "image/boss/black_knight/move/black_knight_backstep(L).bmp", 36, 37, true, RGB(255, 0, 255));
	m_pImg_backStepR = IMAGEMANAGER->addImage("backStepR", "image/boss/black_knight/move/black_knight_backstep(R).bmp", 36, 37, true, RGB(255, 0, 255));
	m_pImg_Atk = IMAGEMANAGER->addImage("basicAtk", "image/boss/black_knight/atk/black_knight_Atk.bmp", 228, 76, 4, 2, true, RGB(255, 0, 255));
	m_pImg_jumpAtk = IMAGEMANAGER->addImage("jumpAtk", "image/boss/black_knight/atk/black_knight_jumpAtk.bmp", 192, 88, 4, 2, true, RGB(255, 0, 255));
	m_pImg_shootAtk_1 = IMAGEMANAGER->addImage("shootAtk", "image/boss/black_knight/atk/black_knight_shootAtk.bmp", 432, 80, 8, 2, true, RGB(255, 0, 255));
	m_pImg_jumpAtk_1L = IMAGEMANAGER->addImage("jumpAtk1L", "image/boss/black_knight/atk/black_knight_jumpAtk_1(L).bmp", 48, 36, true, RGB(255, 0, 255));
	m_pImg_jumpAtk_1R = IMAGEMANAGER->addImage("jumpAtk1R", "image/boss/black_knight/atk/black_knight_jumpAtk_1(R).bmp", 48, 36, true, RGB(255, 0, 255));
	m_pImg_jumpAtk_2 = IMAGEMANAGER->addImage("jumpAtk2", "image/boss/black_knight/atk/black_knight_jumpAtk_2.bmp", 108, 100, 3, 2, true, RGB(255, 0, 255));
	m_pImg_jumpAtk_3L = IMAGEMANAGER->addImage("jumpAtk3L", "image/boss/black_knight/atk/black_knight_jumpAtk_3(L).bmp", 20, 44, true, RGB(255, 0, 255));
	m_pImg_jumpAtk_3R = IMAGEMANAGER->addImage("jumpAtk3R", "image/boss/black_knight/atk/black_knight_jumpAtk_3(R).bmp", 20, 44, true, RGB(255, 0, 255));
	m_pImg_DamageL = IMAGEMANAGER->addImage("damageL", "image/boss/black_knight/death/black_knight_damage(L).bmp", 35, 41, true, RGB(255, 0, 255));
	m_pImg_DamageR = IMAGEMANAGER->addImage("damageR", "image/boss/black_knight/death/black_knight_damage(R).bmp", 35, 41, true, RGB(255, 0, 255));
	m_pImg_Die1 = IMAGEMANAGER->addImage("die1", "image/boss/black_knight/death/black_knight_death_1.bmp", 40, 62, 1, 2, true, RGB(255, 0, 255));
	m_pImg_Die2 = IMAGEMANAGER->addImage("die2", "image/boss/black_knight/death/black_knight_death_2.bmp", 148, 48, 4, 2, true, RGB(255, 0, 255));
	m_pImg_Die3 = IMAGEMANAGER->addImage("die3", "image/boss/black_knight/death/black_knight_death_3.bmp", 37, 48, 1, 2, true, RGB(255, 0, 255));
	
	// 보스 체력 UI 이미지 초기화
	m_pImg_Hp_1 = IMAGEMANAGER->addImage("HP_1", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_pImg_Hp_2 = IMAGEMANAGER->addImage("HP_2", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_pImg_Hp_3 = IMAGEMANAGER->addImage("HP_3", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_pImg_Hp_4 = IMAGEMANAGER->addImage("HP_4", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_pImg_Hp_5 = IMAGEMANAGER->addImage("HP_5", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));
	m_pImg_Hp_6 = IMAGEMANAGER->addImage("HP_6", "image/boss/black_knight/death/black_knight_Hp.bmp", 24, 8, 3, 1, true, RGB(255, 0, 255));

}

void black_Knight::release()
{
	SAFE_DELETE(m_pBulletMgr);
}

void black_Knight::update()
{
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		m_nBossState = BOSS_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		m_nBossState = BOSS_EVENT_IDLE;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		m_nBossState = BOSS_IDLE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		damage(1);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_isJump = true;
	}
	if (m_pBulletMgr)
	{
		m_pBulletMgr->update();
	}
	
	if (m_fX < PLAYER->getPlayerX())	//  플레이어 위치에 따른 프레임 변경
	{
		m_isRight = true;
	}
	if (m_fX > PLAYER->getPlayerX())
	{
		m_isRight = false;
	}

	m_nFrameCount_Die++;
	if (m_nFrameCount_Die % 40 == 0)
	{
		m_nCurrFrameX_Die++;
		if (m_nCurrFrameX_Die > 4)
		{
			m_nCurrFrameX_Die = 4;
			m_nFrameCount_Die = 0;
		}
	}
	fire();
	attack();
	leftFrame();
	rightFrame();
	move();
	attackPhase();
	for (int i = 0; i < MAPMANAGER->getMapVectorRcSize(); i++) {
		jumpAtk(MAPMANAGER->getMapVectorRc(i));
		backStep(MAPMANAGER->getMapVectorRc(i));
		dieMotion(MAPMANAGER->getMapVectorRc(i));
		damageMotion(MAPMANAGER->getMapVectorRc(i));
	}
}

void black_Knight::render(HDC hdc)
{
	renderBoss(hdc);	// 보스렌더
	//renderUI(hdc);
}

void black_Knight::renderBoss(HDC hdc)
{
	if (m_isAlive)
	{
		Rectangle(hdc, rcAtk.left, rcAtk.top, rcAtk.right, rcAtk.bottom);
		Rectangle(hdc, m_rcTemp.left, m_rcTemp.top, m_rcTemp.right, m_rcTemp.bottom);
		Rectangle(hdc, m_rcRange.left, m_rcRange.top, m_rcRange.right, m_rcRange.bottom);
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (!m_isDamage)
		{
			if (m_nBossState == BOSS_EVENT_IDLE)
			{
				if (m_isRight)
				{
					m_pImg_eventIdle->frameRender(hdc, m_fX - 10, m_fY, m_nCurrFrameX_eventIdle, 0);
				}
				else
				{
					m_pImg_eventIdle->frameRender(hdc, m_fX - 10, m_fY, m_nCurrFrameX_eventIdle, 1);
				}
			}
			if (m_nBossState == BOSS_IDLE)
			{
				if (m_isRight)
				{
					m_pImg_Idle->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Idle, 0);
				}
				else
				{
					m_pImg_Idle->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX_Idle, 1);
				}
			}
			if (m_nBossState == BOSS_MOVE)
			{
				if (m_isRight)
				{
					m_pImg_Move->frameRender(hdc, m_fX - 7, m_fY, m_nCurrFrameX_Move, 0);
				}
				else
				{
					m_pImg_Move->frameRender(hdc, m_fX - 7, m_fY, m_nCurrFrameX_Move, 1);
				}
			}
			if (m_nBossState == BOSS_MOVE2)
			{
				if (m_isRight)
				{
					m_pImg_Move->frameRender(hdc, m_fX - 7, m_fY, m_nCurrFrameX_Move, 0);
				}
				else
				{
					m_pImg_Move->frameRender(hdc, m_fX - 7, m_fY, m_nCurrFrameX_Move, 1);
				}
			}
			if (m_nBossState == BOSS_BACKSTEP)
			{
				if (m_isRight)
				{
					m_pImg_backStepR->render(hdc, m_fX - 10, m_fY - 2);
				}
				else
				{
					m_pImg_backStepL->render(hdc, m_fX - 3, m_fY - 2);
				}
			}
			if (m_nBossState == BOSS_BACKSTEP2)
			{
				if (m_isRight)
				{
					m_pImg_backStepR->render(hdc, m_fX - 10, m_fY - 2);
				}
				else
				{
					m_pImg_backStepL->render(hdc, m_fX - 3, m_fY - 2);
				}
			}
			if (m_nBossState == BOSS_ATK)
			{
				if (m_isRight)
				{
					m_pImg_Atk->frameRender(hdc, m_fX - 10, m_fY, m_nCurrFrameX_basicAtk, 0);
				}
				else
				{
					m_pImg_Atk->frameRender(hdc, m_fX - 25, m_fY, m_nCurrFrameX_basicAtk, 1);
				}
			}
			if (m_nBossState == BOSS_JUMP_ATK1)
			{
				if (m_isRight)
				{
					m_pImg_jumpAtk_1R->render(hdc, m_fX - 23, m_fY - 3);
				}
				else
				{
					m_pImg_jumpAtk_1L->render(hdc, m_fX - 5, m_fY - 3);
				}
			}
			if (m_nBossState == BOSS_JUMP_ATK2)
			{
				if (m_isRight)
				{
					m_pImg_jumpAtk_2->frameRender(hdc, m_fX - 10, m_fY - 3, m_nCurrFrameX_jumpAtk2, 0);
				}
				else
				{
					m_pImg_jumpAtk_2->frameRender(hdc, m_fX - 5, m_fY - 3, m_nCurrFrameX_jumpAtk2, 1);
				}
			}
			if (m_nBossState == BOSS_SHOOT_ATK1)
			{
				if (m_isRight)
				{
					m_pImg_shootAtk_1->frameRender(hdc, m_fX - 12, m_fY - 4, m_nCurrFrameX_shootAtk1, 0);
				}
				else
				{
					m_pImg_shootAtk_1->frameRender(hdc, m_fX - 20, m_fY - 4, m_nCurrFrameX_shootAtk1, 1);
				}
			}
			if (m_nBossState == BOSS_DIE1)
			{
				if (m_isRight)
				{
					m_pImg_Die1->frameRender(hdc, m_fX, m_fY, 0, 1);
				}
				else
				{
					m_pImg_Die1->frameRender(hdc, m_fX, m_fY, 0, 1);
				}
			}
			if (m_nBossState == BOSS_DIE2)
			{
				if (m_isRight)
				{
					m_pImg_Die2->frameRender(hdc, m_fX - 8, m_fY + 10, m_nCurrFrameX_Die, 0);
				}
				else
				{
					m_pImg_Die2->frameRender(hdc, m_fX - 8, m_fY + 10, m_nCurrFrameX_Die, 1);
				}
			}
			if (m_nBossState == BOSS_DIE3)
			{
				if (m_isRight)
				{
					m_pImg_Die3->frameRender(hdc, m_fX - 8, m_fY + 10, 0, 0);
				}
				else
				{
					m_pImg_Die3->frameRender(hdc, m_fX - 8, m_fY + 10, 0, 1);
				}
			}
		}
		else
		{
			if (m_nBossState == BOSS_DAMAGE)
			{
				if (m_isRight)
				{
					m_pImg_DamageR->hitRender(hdc, m_fX - 10, m_fY - 5, RGB(200, 0, 0));
				}
				else
				{
					m_pImg_DamageL->hitRender(hdc, m_fX - 3, m_fY - 5, RGB(200, 0, 0));
				}
			}
		}

		if (m_pBulletMgr)
		{
			m_pBulletMgr->render(hdc);
		}
	}
}

void black_Knight::renderUI(HDC hdc)
{
	m_pImg_Hp_1->frameRender(hdc, m_fX_Hp, m_fY_Hp, m_nLife-10, 0);
	m_pImg_Hp_2->frameRender(hdc, m_fX_Hp - 9, m_fY_Hp, m_nLife-8, 0);
	m_pImg_Hp_3->frameRender(hdc, m_fX_Hp - 18, m_fY_Hp, m_nLife-6, 0);
	m_pImg_Hp_4->frameRender(hdc, m_fX_Hp - 27, m_fY_Hp, m_nLife-4, 0);
	m_pImg_Hp_5->frameRender(hdc, m_fX_Hp - 36, m_fY_Hp, m_nLife-2, 0);
	m_pImg_Hp_6->frameRender(hdc, m_fX_Hp - 45, m_fY_Hp, m_nLife, 0);
}

void black_Knight::move()
{
	if (m_isAlive)
	{
		if (m_nBossState == BOSS_MOVE)
		{
			if (m_isRight)
			{
				m_fX += 1.0f;
				m_fY += 0.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
			if (!m_isRight)
			{
				m_fX -= 1.0f;
				m_fY += 0.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
		}
		if (m_nBossState == BOSS_MOVE2)
		{
			if (m_isRight)
			{
				m_fX += 1.0f;
				m_fY += 0.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
			if (!m_isRight)
			{
				m_fX -= 1.0f;
				m_fY += 0.0f;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
		}
	}
}

void black_Knight::backStep(RECT rcGround)
{
	if (m_isAlive && !m_isDamage)
	{
		RECT rc;
		m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
			m_fY + m_pImg_Idle->getFrameHeight() / 2,
			m_pImg_Idle->getFrameWidth(),
			m_pImg_Idle->getFrameHeight());
		if (m_nBossState == BOSS_BACKSTEP)
		{
			if (m_isRight)
			{
				m_fGravity += 0.2f;
				m_fX -= 1.0f;
				m_fY -= m_fBackStepSpeed - m_fGravity;
			}
			else
			{
				m_fGravity += 0.2f;
				m_fX += 1.0f;
				m_fY -= m_fBackStepSpeed - m_fGravity;
			}
		}
		if (IntersectRect(&rc, &m_rc, &rcGround))	// 바닥과의 충돌
		{
			m_isJump = false;
			m_fGravity = 0;
			m_fBackStepSpeed = m_fBackStepSpeed;
			m_fY = rcGround.top - m_pImg_Idle->getFrameHeight();
			m_nBossState = BOSS_BACKSTEP2;
			m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
				m_fY + m_pImg_Idle->getFrameHeight() / 2,
				m_pImg_Idle->getFrameWidth(),
				m_pImg_Idle->getFrameHeight());
		}
		if (m_nBossState == BOSS_BACKSTEP2)
		{
			if (m_isRight)
			{
				m_fGravity += 0.2f;
				m_fX -= 1.0f;
				m_fY -= m_fBackStepSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
			else
			{
				m_fGravity += 0.2f;
				m_fX += 1.0f;
				m_fY -= m_fBackStepSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
		}
		if (IntersectRect(&rc, &m_rc, &rcGround))
		{
			m_isJump = false;
			m_fGravity = 0;
			m_fBackStepSpeed = m_fBackStepSpeed;
			m_fY = rcGround.top - m_pImg_Idle->getFrameHeight();
			m_nBossState = BOSS_SHOOT_ATK1;
			m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
				m_fY + m_pImg_Idle->getFrameHeight() / 2,
				m_pImg_Idle->getFrameWidth(),
				m_pImg_Idle->getFrameHeight());
		}
	}
}

void black_Knight::damage(int damage)
{
	if (m_isAlive)
	{
		m_isDamage = true;
		m_isJump = false;
		m_isAtk = false;
		m_isFire = false;
		m_nBossState = BOSS_DAMAGE;
		m_nLife -= damage;
		if (m_nLife == 0)
		{
			m_nBossState = BOSS_DIE1;
			m_isDying = true;
			m_isDamage = false;
		}

	}
}

void black_Knight::jumpAtk(RECT rcGround)
{
	RECT rc;
	if (m_isAlive && !m_isDying)
	{
		if (m_isJump && (!m_isAtk || !m_isFire))
		{
			if (!m_isRight)
			{
				m_nBossState = BOSS_JUMP_ATK1;
				m_fGravity += 0.2f;
				m_fX -= 1.0f;
				m_fY -= m_fJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
				if (m_fJumpSpeed - m_fGravity < 0 && m_nBossState != BOSS_DAMAGE)
				{
					m_nBossState = BOSS_JUMP_ATK2;
					m_fGravity += 1.0f;
				}

			}
			else
			{
				m_nBossState = BOSS_JUMP_ATK1;
				m_fGravity += 0.2f;
				m_fX += 1.5f;
				m_fY -= m_fJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
				if (m_fJumpSpeed - m_fGravity < 0)
				{
					m_nBossState = BOSS_JUMP_ATK2;
					m_fGravity += 1.0f;
				}
			}
			if (IntersectRect(&rc, &m_rc, &rcGround))
			{
				m_isJump = true;
				m_fGravity = 0;
				m_fJumpSpeed = m_fJumpSpeed;
				m_fY = rcGround.top - m_pImg_Idle->getFrameHeight();
				m_nJumpAtkCount++;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());

				if (m_nJumpAtkCount > 2)
				{
					m_nJumpAtkCount = 0;
					m_nBossState = BOSS_MOVE;
					m_isAtk = false;
					m_isJump = false;
					m_isFire = false;
				}
			}
		}
	}
	
}

void black_Knight::fire()
{
	if (m_isAlive && !m_isDying)
	{
		if (m_isFire && m_nBossState == BOSS_SHOOT_ATK1)
		{
			if (m_nCurrFrameX_shootAtk1 > 4)
			{
				m_nFireCount++;
				if (m_nFireCount % 10 == 0)
				{
					if (m_isRight)
					{
						// 발사
						m_pBulletMgr->fire(m_fX + 15, m_fY + 15, 360.0f * PI / 180, 3.0f, 0);
						m_nBossState = BOSS_MOVE2;
						m_nFireCount = 0;
						m_nCurrFrameX_shootAtk1 = 0;
					}
					else
					{
						// 발사
						m_pBulletMgr->fire(m_fX - 15, m_fY + 15, -180.0f * PI / 180, 3.0f, 1);
						m_nFireCount = 0;
						m_nBossState = BOSS_MOVE2;
						m_nFireCount = 0;
						m_nCurrFrameX_shootAtk1 = 0;
					}

				}
				
			}
		}
	}
}

void black_Knight::attack()
{
	if (m_isAlive && m_isAtk && !m_isJump && !m_isDying)
	{
		if (m_isRight)
		{
			m_nBossState = BOSS_ATK;
			m_nAtkCount++;
			if (m_nAtkCount > 18)
			{
				rcAtk = RectMakeCenter(m_fX + 40, m_fY + 20, 10, 10);
			}
			if (m_nAtkCount == 50)
			{
				rcAtk = RectMakeCenter(-1000, -1000, 10, 10);
				m_nBasicAtkCount++;
				m_nAtkCount = 0;
			}
		}
		else
		{
			m_nBossState = BOSS_ATK;
			m_nAtkCount++;
			if (m_nAtkCount > 18)
			{
				rcAtk = RectMakeCenter(m_fX - 20, m_fY+20, 10, 10);
			}
			if (m_nAtkCount == 50)
			{
				rcAtk = RectMakeCenter(-1000, -1000, 10, 10);
				m_nBasicAtkCount++;
				m_nAtkCount = 0;
			}
		}
	}
}

void black_Knight::rightFrame()
{
	if (m_isAlive && !m_isDying)
	{
		if (m_isRight)
		{
			// 기본 idle
			if (m_nBossState == BOSS_IDLE)
			{
				m_nFrameCount_Idle++;
				if (m_nFrameCount_Idle % 10 == 0)
				{
					m_nCurrFrameX_Idle++;
					if (m_nCurrFrameX_Idle > 2)
					{
						m_nCurrFrameX_Idle = 0;
						m_nFrameCount_Idle = 0;
						m_nEventIdleCount++;
						if (m_nEventIdleCount > 3)
						{
							m_nBossState = BOSS_MOVE;
						}
					}
				}
			}
			// 이벤트 idle
			if (m_nBossState == BOSS_EVENT_IDLE)
			{
				m_nFrameCount_eventIdle++;
				if (m_nFrameCount_eventIdle % 10 == 0)
				{
					m_nCurrFrameX_eventIdle++;
					if (m_nCurrFrameX_eventIdle > 2)
					{
						m_nCurrFrameX_eventIdle = 0;
						m_nFrameCount_eventIdle = 0;
					}

				}
			}
			// 무브
			if (m_nBossState == BOSS_MOVE)
			{
				m_nFrameCount_Move++;
				if (m_nFrameCount_Move % 10 == 0)
				{
					m_nCurrFrameX_Move++;
					if (m_nCurrFrameX_Move > 6)
					{
						m_nMoveCount++;
						m_nCurrFrameX_Move = 0; 
						m_nFrameCount_Move = 0;
						if (m_nMoveCount == 2)
						{
							m_nBossState = BOSS_ATK;
							m_isAtk = true;
							m_nMoveCount = 0;
						}
					}
				}
			}
			if (m_nBossState == BOSS_MOVE2)
			{
				m_nFrameCount_Move++;
				if (m_nFrameCount_Move % 10 == 0)
				{
					m_nCurrFrameX_Move++;
					if (m_nCurrFrameX_Move > 6)
					{
						m_nMoveCount++;
						m_nCurrFrameX_Move = 0;
						m_nFrameCount_Move = 0;
						if (m_nMoveCount == 2)
						{
							m_nBossState = BOSS_JUMP_ATK1;
							m_isJump = true;
							m_nMoveCount = 0;
						}
					}
				}
			}
			// 기본공격
			if (m_nBossState == BOSS_ATK)
			{
				m_nFrameCount_basicAtk++;
				if (m_nFrameCount_basicAtk % 10 == 0)
				{
					m_nCurrFrameX_basicAtk++;
					if (m_nCurrFrameX_basicAtk > 4)
					{
						m_nCurrFrameX_basicAtk = 0;
						m_nFrameCount_basicAtk = 0;
					}
				}
			}
			// 점프공격
			if (m_nBossState == BOSS_JUMP_ATK2)
			{
				m_nFrameCount_jumpAtk2++;
				if (m_nFrameCount_jumpAtk2 % 5 == 0)
				{
					m_nCurrFrameX_jumpAtk2++;
					if (m_nCurrFrameX_jumpAtk2 > 3)
					{
						m_nCurrFrameX_jumpAtk2 = 0;
						m_nFrameCount_jumpAtk2 = 0;
					}
				}
			}
			if (m_nBossState == BOSS_SHOOT_ATK1)
			{
				m_nFrameCount_shootAtk1++;
				if (m_nFrameCount_shootAtk1 % 10 == 0)
				{
					m_nCurrFrameX_shootAtk1++;
					if (m_nCurrFrameX_shootAtk1 > 8)
					{
						//m_nCurrFrameX_shootAtk1 = 0;
						m_nFrameCount_shootAtk1 = 0;
					}
				}
			}
		}
	}
}

void black_Knight::leftFrame()
{
	if (m_isAlive && !m_isDying)
	{
		if (!m_isRight)
		{
			m_nFrameCount_Idle++;
			if (m_nFrameCount_Idle % 10 == 0)
			{
				m_nCurrFrameX_Idle--;
				if (m_nCurrFrameX_Idle < 0)
				{
					m_nCurrFrameX_Idle = 2;
					m_nFrameCount_Idle = 0;
					m_nEventIdleCount++;
					if (m_nEventIdleCount > 3)
					{
						m_nBossState = BOSS_MOVE;
					}
				}
			}
			m_nFrameCount_eventIdle++;
			if (m_nFrameCount_eventIdle % 10 == 0)
			{
				m_nCurrFrameX_eventIdle--;
				if (m_nCurrFrameX_eventIdle < 0)
				{
					m_nCurrFrameX_eventIdle = 2;
					m_nFrameCount_eventIdle = 0;
				}
			}
			if (m_nBossState == BOSS_MOVE)
			{
				m_nCurrFrameX_shootAtk1 = 0;
				m_nFrameCount_Move++;
				if (m_nFrameCount_Move % 10 == 0)
				{
					m_nCurrFrameX_Move--;
					if (m_nCurrFrameX_Move < 0)
					{
						m_nMoveCount++;
						m_nCurrFrameX_Move = 6;
						m_nFrameCount_Move = 0;
						if (m_nMoveCount == 2)
						{
							m_nBossState = BOSS_ATK;
							m_isAtk = true;
							m_nMoveCount = 0;
						}
					}
				}
			}
			if (m_nBossState == BOSS_MOVE2)
			{
				m_nFrameCount_Move++;
				if (m_nFrameCount_Move % 10 == 0)
				{
					m_nCurrFrameX_Move--;
					if (m_nCurrFrameX_Move < 0)
					{
						m_nMoveCount++;
						m_nCurrFrameX_Move = 6;
						m_nFrameCount_Move = 0;
						if (m_nMoveCount == 2)
						{
							m_nBossState = BOSS_JUMP_ATK1;
							m_isJump = true;
							m_nMoveCount = 0;
						}
					}
				}
			}
			if (m_nBossState == BOSS_ATK)
			{
				m_nFrameCount_basicAtk++;
				if (m_nFrameCount_basicAtk % 10 == 0)
				{
					m_nCurrFrameY_basicAtk = 1;
					m_nCurrFrameX_basicAtk--;
					if (m_nCurrFrameX_basicAtk < 0)
					{
						m_nCurrFrameX_basicAtk = 4;
						m_nFrameCount_basicAtk = 0;
					}
				}
			}
			if (m_nBossState == BOSS_JUMP_ATK2)
			{
				m_nFrameCount_jumpAtk2++;
				if (m_nFrameCount_jumpAtk2 % 5 == 0)
				{
					m_nCurrFrameY_jumpAtk2 = 1;
					m_nCurrFrameX_jumpAtk2++;
					if (m_nCurrFrameX_jumpAtk2 > 3)
					{
						m_nCurrFrameX_jumpAtk2 = 0;
						m_nFrameCount_jumpAtk2 = 0;
					}
				}
			}
			if (m_nBossState == BOSS_SHOOT_ATK1)
			{
				m_nFrameCount_shootAtk1++;
				if (m_nFrameCount_shootAtk1 % 10 == 0)
				{
					m_nCurrFrameX_shootAtk1++;
					if (m_nCurrFrameX_shootAtk1 > 8)
					{
						m_nBossState = BOSS_MOVE2;
						m_nFrameCount_shootAtk1 = 0;
					}
				}
			}
		}
	}
}

void black_Knight::attackPhase()
{
	if (m_isAlive && !m_isDying)
	{
		if (m_nBossState == BOSS_ATK)
		{
			// 기본공격
			m_isAtk = true;
			if (m_nBasicAtkCount == 1)
			{
				m_nBasicAtkCount = 0;
				m_nBossState = BOSS_BACKSTEP;
				m_isAtk = false;
				m_isJump = false;
				m_isFire = false;
			}
		}
		if (m_nBossState == BOSS_SHOOT_ATK1)
		{
			// 슈팅공격
			m_isFire = true;
			if (m_nShootAtkCount == 1)
			{
				m_nShootAtkCount = 0;
				m_nBossState = BOSS_JUMP_ATK1;
				m_isAtk = false;
				m_isJump = true;
				m_isFire = false;
			}
		}
		if (m_nBossState == BOSS_JUMP_ATK1)
		{
			// 점프공격
			m_isJump = true;
			if (m_nJumpAtkCount > 2)
			{
				m_nJumpAtkCount = 0;
				m_nBossState = BOSS_MOVE;
				m_isAtk = false;
				m_isJump = false;
				m_isFire = false;
			}
		}
	}
}

void black_Knight::dieMotion(RECT rcGround)
{
	if (m_isAlive)
	{
		RECT rc;
		if (m_nBossState == BOSS_DIE1)
		{
			if (m_isRight)
			{
				m_fGravity += 0.2f;
				m_fX -= 2.0f;
				m_fY -= m_fDieJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
			else
			{
				m_fGravity += 0.2f;
				m_fX += 2.0f;
				m_fY -= m_fDieJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}

			if (m_fDieJumpSpeed - m_fGravity < 0)
			{
				m_nBossState = BOSS_DIE2;
			}
		}
		if (m_nBossState == BOSS_DIE2)
		{

			if (m_isRight)
			{
				m_fGravity += 0.2f;
				m_fX -= 2.0f;
				m_fY -= m_fDieJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
			else
			{
				m_fGravity += 0.2f;
				m_fX += 2.0f;
				m_fY -= m_fDieJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
			}
		}
		if (IntersectRect(&rc, &m_rc, &rcGround))	// 바닥과의 충돌
		{
			m_isJump = false;
			m_isAtk = false;
			m_isFire = false;
			m_fGravity = 0;
			m_fDieJumpSpeed = 0;
			m_nBossState = BOSS_DIE3;
			m_fY = rcGround.top - m_pImg_Idle->getFrameHeight();
			m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
				m_fY + m_pImg_Idle->getFrameHeight() / 2,
				m_pImg_Idle->getFrameWidth(),
				m_pImg_Idle->getFrameHeight());
		}
	}
}

void black_Knight::damageMotion(RECT rcGround)
{
	if (m_isDamage)
	{
		RECT rc;
		m_nDamageTime++;
		m_nBossState = BOSS_DAMAGE;
		if (m_isRight)
		{
			if (m_nDamageTime < 17)
			{
				m_fGravity += 1.0f;
				m_fX -= 2.0f;
				m_fY -= m_fDamageJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
				if (IntersectRect(&rc, &m_rc, &rcGround))
				{
					m_nBossState = BOSS_MOVE;
					m_nDamageTime = 0;
					m_isDamage = false;
				}
			}
		}
		else
		{
			if (m_nDamageTime < 17)
			{
				m_fGravity += 1.0f;
				m_fX += 2.0f;
				m_fY -= m_fDamageJumpSpeed - m_fGravity;
				m_rc = RectMakeCenter(m_fX + m_pImg_Idle->getFrameWidth() / 2,
					m_fY + m_pImg_Idle->getFrameHeight() / 2,
					m_pImg_Idle->getFrameWidth(),
					m_pImg_Idle->getFrameHeight());
				if (IntersectRect(&rc, &m_rc, &rcGround))
				{
					m_nBossState = BOSS_MOVE;
					m_nDamageTime = 0;
					m_isDamage = false;
				}
			}
		}
	}
}
