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

	RECT	m_rc;
	RECT	m_InvenRect;

	float	m_fX, m_fY;
	float	m_fSpeed;

	float	m_invenX, m_invenY;
	
	int		tempRan;
	int		Money;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

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

