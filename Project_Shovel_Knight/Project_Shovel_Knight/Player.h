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

enum PlayerState
{
	P_APPEAR, P_IDLE, P_MOVERIGHT, P_MOVELEFT, P_ATTACK, P_MAGIC, P_JUMP, P_NUM
};

class Player : public singletonBase<Player>
{
private:

	vector<Temp> v_VecTemp;
	vector<Temp>::iterator v_Iter;

	Inventory*	m_inventory;
	Equipment*	m_Equipment;

	Temp m_Drop;
	image * m_PlayerImg;
	image*	m_UI;
	image * m_img;
	image *	m_magicimg;
	image *	m_ballimg;
	image *	m_startimg;
	image * m_moveimg;
	image * m_attackimg;
	image * m_jumpimg;
	image *	m_jumpdownimg;
	image *	m_jumpatkimg;

	RECT	m_rc;

	PlayerState		State;

	
	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;
	int		m_nleftCount;
	int		m_nrightCount;
	int		m_nShotCount;
	float	m_fSpeed;
	float	m_fX;
	float	m_fY;

	bool		m_bIsAppear;
	bool		m_bIsAttck = false;
	bool		m_bIsjumpAtk = false;
	bool		m_bIsjump = false;

	float gravity;
	float Jumpspeed;
	
	int		tempRan;
	int		Money;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void Attack();
	void Move();
	void RectColliosion(RECT x);

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

