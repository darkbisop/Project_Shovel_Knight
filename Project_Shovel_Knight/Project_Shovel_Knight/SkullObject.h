#pragma once
#include "obejectBasicInfo.h"

class SkullObject : public obejectBasicInfo
{
private:

	image* m_Img;

	float m_fX, m_fY, m_angle, m_gravity;
	bool	MoveRight;
	bool	MoveLeft;

public:

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline RECT getRect() { return _rc; }

	inline float getY() { return m_fY; }
	inline void SetY(float a) { m_fY = a; }
	inline void setGravity(float a) { m_gravity = a; }
	inline float getGravity() { return m_gravity; }

	inline bool getMoveLeft() { return MoveLeft; }
	inline void setMoveLeft(bool a) { MoveLeft = a; }

	inline bool getMoveRight() { return MoveRight; }
	inline void setMoveRight(bool a) { MoveRight = a; }

	SkullObject();
	~SkullObject();
};

