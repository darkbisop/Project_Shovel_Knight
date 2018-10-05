#pragma once
#include "singletonBase.h"
#include "Equipment.h"
#include "Inventory.h"

struct Temp
{
	float x;
	float y;
	float angle;
	RECT rc;
	float	gravity;
	float speed;
};

enum State
{
	P_APPEAR, P_IDLE, P_MOVERIGHT, P_MOVELEFT, P_ATTACK, P_DOWNATTACK, P_MAGIC, P_JUMP, P_NUM
};

class Player : public singletonBase<Player>
{
private:

	vector<Temp> v_VecTemp;
	vector<Temp>::iterator v_Iter;

	Inventory*	m_inventory;
	Equipment*	m_Equipment;

	Temp	m_Drop;
	RECT	m_rc;
	State	m_State;

	image*	m_UI;
	image*	m_IdleImg;
	image*	m_MoveImg;
	image*	m_JumpImg;
	image*	m_JumpLeftImg;
	image*	m_JumpDown;
	image*	m_JumpDownLeft;
	image*	m_AttackImg;
	image*	m_AttackDownImg;
	image*	m_DownLeftImg;

	int		m_CurrFrameX;
	int		m_CurrFrameY;
	int		m_FrameCount;
	int		m_AtkFrameCount;

	float	m_fSpeed;
	float	m_fX;
	float	m_fY;

	float	gravity;
	float	jumpSpeed;

	bool	m_isRight;
	bool	m_isAttack;
	bool	m_isAirAttack;
	bool	m_isGround;
	
	int		tempRan;
	int		Money;

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

	inline RECT getPlayerRect() { return m_rc; }
	inline float getPlayerX() { return m_fX; }
	inline float getPlayerY() { return m_fY; }

	inline void SetPlayerX(float x) { m_fX = x; }
	inline void SetPlayerY(float y) { m_fY = y; }

	inline int getMoney() { return Money; }
	inline void setMoney(int a) { Money = a; }

	inline Inventory* getInventory() { return m_inventory; }

	Player();
	~Player();
};

