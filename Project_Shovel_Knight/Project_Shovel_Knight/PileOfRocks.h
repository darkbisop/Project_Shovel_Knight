#pragma once
#include "obejectBasicInfo.h"

struct tagJewelInfo
{
	float x;
	float y;
	float angle;
	RECT rc;
	float gravity;
	float speed;
	bool isAlive;
	int RandGem;
	bool soundOn;
};

class PileOfRocks : obejectBasicInfo
{
private:

	vector<tagJewelInfo> v_VecJewel;
	vector<tagJewelInfo>::iterator v_Iter;

	tagJewelInfo m_Drop;

	image* m_Img;
	image* m_Gems;

	int RanD;
	int RandGems;

	float m_fX, m_fY, m_angle, m_gravity;

public:

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void DigOut();

	inline RECT getRect() { return _rc; }
	inline void setGravity(float a) { m_Drop.gravity = a; }

	inline float getY() { return m_fY; }
	inline void SetY(float a) { m_fY = a; }

	PileOfRocks();
	~PileOfRocks();
};

