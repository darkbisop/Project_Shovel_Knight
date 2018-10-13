#pragma once
#include "obejectBasicInfo.h"

class movingFloor : public obejectBasicInfo
{
private:

	image* m_img;
	float m_fX, m_fY, m_fSpeed;

	RECT m_rangeRC;
	int movingPatt;

	bool m_isRight;
	bool m_isUp;
	bool m_upMove;
	bool m_rightMove;

public:

	virtual HRESULT init(float x, float y, float rangeX, float rangeY, bool Right, bool up, bool moveRight, bool moveUp, float speed);

	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline RECT getRect() { return _rc; }
	inline bool getIsRight() { return m_isRight; }
	inline bool getIsUp() { return m_isUp; }

	inline bool getMoveUp() { return m_upMove; }
	inline bool getMoveRight() { return m_rightMove; }

	movingFloor();
	~movingFloor();
};

