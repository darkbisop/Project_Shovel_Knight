#pragma once
#include "singletonBase.h"
#include "Equipment.h"
#include "Inventory.h"

enum State
{
	P_APPEAR, P_IDLE, P_MOVE, P_ATTACK, P_DOWNATTACK, P_MAGIC, P_JUMP, P_LADDERUP, P_LADDERSTOP, P_DAMAGED
};

class Player : public singletonBase<Player>
{
private:

	Inventory*	m_inventory;
	Equipment*	m_Equipment;

	RECT	m_rc;
	RECT	m_AttackRc;
	RECT	m_AttackDownRc;
	State	m_State;

	image*	m_UI;
	image*	m_IdleImg;
	image*	m_MoveImg;
	image*	m_JumpImg;
	image*	m_JumpDown;
	image*	m_AttackImg;
	image*	m_AttackDownImg;
	image*	m_LadderUpImg;
	image*	m_DamagedImg;
	image*	m_AppearImg;

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
	bool	m_invincibleTime;
	bool	m_isDamaged;
	bool	m_isAppear;
	
	int		Money;
	int		m_DamagedTime;
	int		m_AppearTime;
	int		m_invincibleCount;
	int		m_invincibleAlpha;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void KeyProcess();
	void Animation();
	void ShovelRender(HDC hdc);
	void RectColliosion(RECT x);
	void LadderColliosion(RECT x);
	void DownATKCollision(RECT x);
	void DownATKtoOBJCollision(RECT x);
	void OBJCollision(RECT x);

	inline RECT getPlayerRect() { return m_rc; }
	inline RECT getAttacRect() { return m_AttackRc; }
	inline RECT getAttacDWRect() { return m_AttackDownRc; }

	inline float getPlayerX() { return m_fX; }
	inline float getPlayerY() { return m_fY; }

	inline void SetPlayerX(float x) { m_fX = x; }
	inline void SetPlayerY(float y) { m_fY = y; }

	inline int getMoney() { return Money; }
	inline void setMoney(int a) { Money = a; }

	inline void setAppear(bool a) { m_isAppear = a; }

	inline bool getInvincibleTime() { return m_invincibleTime; }
	inline void setInvincibleTime(bool a) { m_invincibleTime = a; }

	inline bool getIsDamaged() { return m_isDamaged; }
	inline void setIsDamaged(bool a) { m_isDamaged = a; }

	inline Inventory* getInventory() { return m_inventory; }

	Player();
	~Player();
};

