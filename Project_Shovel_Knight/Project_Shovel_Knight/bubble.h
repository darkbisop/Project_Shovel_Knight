#pragma once
class bubble
{
protected:
	image*	m_pImg;
	RECT	m_rc;
	float	m_fX;
	float	m_fY;
	float	m_fFiredX;
	float	m_fFiredY;
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fRange;
	bool	m_isFire;
	bool	m_isAlive;
	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nFrameCount;
	int		m_nBubbleCount;

public:
	virtual HRESULT init();
	virtual HRESULT init(const char* szImageName, float speed,
		float x, float y, float angle, float range);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void fire(float x, float y);
	void move();

	inline RECT getRECT() { return m_rc; }
	inline float getX() { return m_fX; }
	inline void setX(float x) { m_fX = x; }

	inline float getY() { return m_fY; }
	inline void setY(float x) { m_fY = x; }

	inline bool getIsAlive() { return m_isAlive; }
	inline void setIsAlive(bool a) { m_isAlive = a; }

	bubble();
	~bubble();
};

