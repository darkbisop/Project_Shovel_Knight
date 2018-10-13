#pragma once
#include "obejectBasicInfo.h"

class BubleBuble : public obejectBasicInfo
{
private:

	image* m_img;
	float m_fX, m_fY, m_fSpeed;

	RECT m_rangeRC;
	bool m_isUp;

	int nFrameCount;
	int m_nCurrFrameX;

public:

	virtual HRESULT init(float x, float y, float rangeY, bool up);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline RECT getRect() { return _rc; }
	inline bool getIsAlive() { return _isAlive; }
	inline void setIsAlive(bool a) { _isAlive = a; }

	BubleBuble();
	~BubleBuble();
};

