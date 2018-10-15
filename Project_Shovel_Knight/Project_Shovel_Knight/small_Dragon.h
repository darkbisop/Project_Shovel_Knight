#pragma once
#include "enemyInfo.h"

enum smallDG_State
{
	smallDG_UPDOWN, smallDG_STRAIGHT, smallDG_CIRCLE, smallDG_NULL
};

class small_Dragon : public enemyInfo
{
private:
	image*	m_pImg_HitR;
	image*	m_pImg_HitL;

	smallDG_State m_pSmallDG_State;

	RECT	m_rcUpDownRange;
	RECT	m_rcStraightRange;

	float	m_destX;
	float	m_destY;
	float	m_fRightAngle;
	float	m_fLeftAngle;
	bool	m_isUp;			// 위아래 움직임을 확인 할 변수
	bool	m_isRightRun;	// 좌우 움직임(빠른움직임)을 확인 할 변수
	int		m_nScalar;
	int		m_nDamageCount;
	int		m_nPhase;

	bool	m_isCrash;

public:
	virtual HRESULT init(float x, float y, smallDG_State phase);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void damage(int damage);

	inline int getHP() { return m_nLife; }
	inline bool getCrash() { return m_isCrash; }
	inline void setCrash(bool a) { m_isCrash = a; }

	small_Dragon();
	~small_Dragon();
};

