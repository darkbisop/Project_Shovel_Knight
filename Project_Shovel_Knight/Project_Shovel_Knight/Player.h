#pragma once

class RunAndGunScene;

enum Player_State
{
	IDLE, MOVE
};
class Player
{
private:

	Player_State m_State;
	image * m_PlayerImg;

	RECT	m_rc;

	float	m_fX, m_fY;
	float	m_fSpeed;

	int		m_Hp;
	int		m_Money;

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

	Player();
	~Player();
};
