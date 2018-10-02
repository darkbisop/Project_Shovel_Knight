#pragma once

struct Temp
{
	float x;
	float y;
	float angle;
	RECT rc;
	float	gravity;
	float speed;
};

enum Player_State
{
	IDLE, MOVE
};
class Player
{
private:

	vector<Temp> v_VecTemp;
	vector<Temp>::iterator v_Iter;

	Temp m_Drop;
	Player_State m_State;
	image * m_PlayerImg;
	image * m_InventoryImg;

	RECT	m_rc;
	RECT	m_InvenRect;

	float	m_fX, m_fY;
	float	m_fSpeed;

	float	m_invenX, m_invenY;
	
	int		tempRan;
	int		m_InvenX;
	int		m_InvenY;

	bool	m_isMoving;
	bool	m_isInventoryOn;

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

	inline bool	getIsMoving() { return m_isMoving; }
	inline void setIsMoving(bool a) { m_isMoving = a; }

	Player();
	~Player();
};

