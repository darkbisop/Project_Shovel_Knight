#pragma once
#include "scene.h"

enum State_Temp
{
	TempAttack, TempIdle, TempJump, TempDownATK, TempMove
};

class TestScene : public scene
{
private:

	RECT	m_rc;
	RECT	m_AttackRc;
	RECT	m_AttackDownRc;
	State_Temp	m_State;
	
	image*	BG;
	image*	m_IdleImg;
	image*	m_MoveImg;
	image*	m_JumpImg;
	image*	m_JumpDown;
	image*	m_AttackImg;
	image*	m_AttackDownImg;
	
	int		m_CurrFrameX;
	int		m_CurrFrameY;
	int		m_FrameCount;
	int		m_AtkFrameCount;
	int		m_AttackCount;
	
	float	m_fSpeed;
	float	m_fX;
	float	m_fY;
	
	float	gravity;
	float	jumpSpeed;
	
	bool	m_isRight;
	bool	m_isAttack;
	bool	m_isGround;
	bool	m_isFalling;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void KeyProcess();
	void Animation();
	void ShovelRender(HDC hdc);
	void Colliosion();

	TestScene();
	~TestScene();
};

