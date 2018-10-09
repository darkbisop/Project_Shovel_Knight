#pragma once
#include "obejectBasicInfo.h"

struct tagJewel
{
	float x;
	float y;
	float angle;
	RECT rc;
	float gravity;
	float speed;
	bool isAlive;
	int RandGem;
};

class dirtBlock : public obejectBasicInfo
{
private:

	vector<tagJewel> v_VecJewel;
	vector<tagJewel>::iterator v_Iter;

	tagJewel m_Drop;

	image* m_Img;
	image* m_Sprite;
	image* m_Gems;

	int m_FrameCount;
	int	CurrFrame;
	int RanD;
	int RandGems;
	bool m_crash;

	float m_fX, m_fY, m_angle, m_gravity;

public:

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void animation();
	void DigOut();
	void COllision();

	inline bool getCrash() { return m_crash; }
	inline void setCrash(bool a) { m_crash = a; }

	inline void setAlive(bool a) { _isAlive = a; }

	inline RECT getRect() { return _rc; }
	inline void setGravity(float a) { m_Drop.gravity = a; }

	inline float getY() { return m_fY; }
	inline void SetY(float a) { m_fY = a; }

	dirtBlock();
	~dirtBlock();
};

