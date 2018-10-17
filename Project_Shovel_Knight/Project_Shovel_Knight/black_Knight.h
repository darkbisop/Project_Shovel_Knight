#pragma once
#include "enemyInfo.h"

class bulletManager;

enum boss_state
{
	BOSS_EVENT_IDLE, BOSS_IDLE,
	BOSS_MOVE, BOSS_MOVE2,
	BOSS_DAMAGE,
	BOSS_ATK,
	BOSS_JUMP_ATK1, BOSS_JUMP_ATK2,
	BOSS_SHOOT_ATK1,
	BOSS_BACKSTEP,
	BOSS_DIE1, BOSS_DIE2, BOSS_DIE3
};

class black_Knight : public enemyInfo
{
private:
	image*	m_pImg_eventIdle;
	image*	m_pImg_backStepL;
	image*	m_pImg_backStepR;
	image*	m_pImg_jumpAtk;
	image*	m_pImg_jumpAtk_1L;
	image*	m_pImg_jumpAtk_1R;
	image*	m_pImg_jumpAtk_2;
	image*	m_pImg_jumpAtk_3L;
	image*	m_pImg_jumpAtk_3R;
	image*	m_pImg_shootAtk_1;
	image*	m_pImg_shootAtk_2;
	image*	m_pImg_DamageL;
	image*	m_pImg_DamageR;
	image*	m_pImg_Die1;
	image*	m_pImg_Die2;
	image*	m_pImg_Die3;


	// 보스 체력 UI
	image*	m_pImg_Hp_1;
	image*	m_pImg_Hp_2;
	image*	m_pImg_Hp_3;
	image*	m_pImg_Hp_4;
	image*	m_pImg_Hp_5;
	image*	m_pImg_Hp_6;

	float	m_fX_Hp;
	float	m_fY_Hp;

	bulletManager*	m_pBulletMgr;

	boss_state m_nBossState;

	RECT	m_rcRange;
	RECT	m_rcTemp;

	RECT	rcAtk;

	bool	m_isAtk;
	bool	m_isJump;
	bool	m_isLeft;

	float	m_fBackStepSpeed;
	float	m_fDamageJumpSpeed;
	float	m_fDieJumpSpeed;
	float	m_fGravity_BackStep;
	float	m_fGravity_Damage;
	float	m_fGravity_Die;
	int		m_nEventIdleCount;
	int		m_nEventIdleCount2;

	// 어택 별 카운트 ( 패턴에 필요함 )
	int		m_nAtkCount;
	int		m_nAtkCount2;
	int		m_nJumpAtkCount;
	int		m_nJumpAtkCount2;
	int		m_nMoveCount;
	int		m_nMoveCount2;
	int		m_nMoveCount_2;
	int		m_nMoveCount2_2;
	int		m_nBasicAtkCount;
	int		m_nBasicAtkCount2;
	int		m_nShootAtkCount;
	int		m_nShootAtkCount2;

	// 프레임 카운트
	int		m_nCurrFrameX_eventIdle;
	int		m_nCurrFrameY_eventIdle;
	int		m_nFrameCount_eventIdle;

	int		m_nCurrFrameX_basicAtk;
	int		m_nCurrFrameY_basicAtk;
	int		m_nFrameCount_basicAtk;

	int		m_nCurrFrameX_jumpAtk;
	int		m_nCurrFrameY_jumpAtk;
	int		m_nFrameCount_jumpAtk;

	int		m_nCurrFrameX_jumpAtk2;
	int		m_nCurrFrameY_jumpAtk2;
	int		m_nFrameCount_jumpAtk2;

	int		m_nCurrFrameX_shootAtk1;
	int		m_nCurrFrameY_shootAtk1;
	int		m_nFrameCount_shootAtk1;

	int		m_nCurrFrameX_shootAtk2;
	int		m_nCurrFrameY_shootAtk2;
	int		m_nFrameCount_shootAtk2;

public:
	HRESULT init(float x, float y);
	void initImg();
	void release();
	void update();
	void render(HDC hdc);
	void renderBoss(HDC hdc);
	void renderUI(HDC hdc);
	
	void move();
	void fire();
	void attack();
	void rightFrame();
	void leftFrame();

	void damage(int damage);
	void backStep(RECT rcGround);
	void jumpAtk(RECT rcGround);
	void dieMotion(RECT rcGround);
	void damageMotion(RECT rcGround);

	inline RECT getRectTemp() { return m_rcTemp; }
	black_Knight();
	~black_Knight();
};

