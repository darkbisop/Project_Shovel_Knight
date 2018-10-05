#pragma once

class bug
{
private:
	image*	m_pImg_Move;
	image*	m_pImg_Die;
	RECT	m_rc;
	RECT	m_rcRange;
	RECT	m_tempRc;		// 이펙트 출력을 위한 임의의 RECT 배틀씬에서 충돌처리 할 생각
	
	int		m_nPower;
	float	m_fRange;
	float	m_destX;
	float	m_destY;
	float	m_fSpeed;
	float	m_fRightAngle;
	float	m_fLeftAngle;
	bool	m_isRight;		// 움직임을 확인 할 변수
	bool	m_isDying;		// 죽는 모션
	float m_fX;
	float m_fY;
	bool m_isAlive;
	int m_nLife;

	//SYNTHESIZE(bool, m_isAlive, IsAlive);
	//SYNTHESIZE(float, m_fX, X);
	//SYNTHESIZE(float, m_fY, Y);
	//SYNTHESIZE(int, m_nLife, Life);

	// 이미지 ( move인 상태 )
	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nFrameCount;
	int		m_nScalar;

	// 이미지 ( die 상태 )
	int		m_nDieFrameX;
	int		m_nDieFrameY;
	int		m_nDieFrameCount;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void dieMove();
	void damage(int damage);
	void moveFrame();
	void dieFrame();
	void frameChange();
	void collide();

	inline int getX() { return m_fX; }
	inline int getY() { return m_fY; }
	inline RECT getRect() { return m_rc; }
	inline void setAlive(bool a) { m_isAlive = a; }


	bug();
	~bug();
};

