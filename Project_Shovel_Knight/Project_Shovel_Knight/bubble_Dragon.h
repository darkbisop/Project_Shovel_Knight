#pragma once
class objectManager;

enum bubble_dragon
{
	BUBBLEDG_IDLE, BUBBLEDG_ATK, BUBBLEDG_MOVE, BUBBLEDG_HIT, BUBBLEDG_DIE
};
class bubble_Dragon
{
private:
	image*	m_pImg_Idle;
	image*	m_pImg_Move;
	image*	m_pImg_Atk;
	image*	m_pImg_Hit;
	image*	m_pImg_Die;
	RECT	m_rc_Head;
	RECT	m_rc_Body;
	RECT	m_rc_Effect;
	objectManager*	m_pBubbleMgr;
	bubble_dragon bubbleDG_state;
	int		m_nLife;
	int		m_nPower;
	float	m_fX;
	float	m_fY;
	float	m_fSpeed;
	float	m_fRange;
	bool	m_isAlive;
	bool	m_isAtk;
	bool	m_isDamage;		// 공격을 당했을 때를 확인 할 변수
	bool	m_isMove;
	bool	m_isDying;

	int		m_nFireCount;
	int		m_nEffectCount;
	// idle
	int		m_nCurrFrameX_Idle;
	int		m_nCurrFrameY_Idle;
	int		m_nFrameCount_Idle;

	// move
	int		m_nCurrFrameX_Move;
	int		m_nCurrFrameY_Move;
	int		m_nFrameCount_Move;

	// atk
	int		m_nCurrFrameX_Atk;
	int		m_nCurrFrameY_Atk;
	int		m_nFrameCount_Atk;

	// hit
	int		m_nCurrFrameX_Hit;
	int		m_nCurrFrameY_Hit;
	int		m_nFrameCount_Hit;

	// die
	int		m_nCurrFrameX_Die;
	int		m_nCurrFrameY_Die;
	int		m_nFrameCount_Die;
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void damage(int damage);
	void fire();
	void frameCount();
	void dieEffect();

	inline RECT getHead() { return m_rc_Head; }
	inline RECT getBody() { return m_rc_Body; }

	inline int getLife() { return m_nLife; }

	bubble_Dragon();
	~bubble_Dragon();
};

