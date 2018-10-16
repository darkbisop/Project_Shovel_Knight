#pragma once
class bullet
{
protected:
	image * m_pImg;
	RECT	m_rc;
	float	m_fSpeed;
	float	m_fX, m_fY;
	float	m_fFiredX, m_fFiredY;
	float	m_fAngle;
	float	m_fRange;
	bool	m_isFire;
	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nFrameCount;


public:
	virtual HRESULT init();
	virtual HRESULT init(const char* szImageName, float speed,
		float x, float y, float angle, float range, int currFrameY);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void fire(float x, float y);
	virtual void move();
	bullet();
	~bullet();
};

