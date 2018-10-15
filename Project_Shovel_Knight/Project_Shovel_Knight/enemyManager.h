#pragma once
#include <vector>
#include "bug.h"
#include "bubble_Dragon.h"
#include "small_Dragon.h"

class enemyManager
{
private:

	vector<bug*> m_VecBug;
	vector<bug*>::iterator m_IterBug;

	vector<bubble_Dragon*> m_VecBBD;
	vector<bubble_Dragon*>::iterator m_IterBBD;

	vector<small_Dragon*> m_VecSmallDRG;
	vector<small_Dragon*>::iterator m_IterSmallDRG;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setBug();
	void setBubleDragon();
	void setSmallDragon();

	inline vector<bug*> getVecBug() { return m_VecBug; }
	inline vector<bug*>::iterator getIterBug() { return m_IterBug; }

	inline vector<bubble_Dragon*> getVecBBD() { return m_VecBBD; }
	inline vector<bubble_Dragon*>::iterator getIterBBD() { return m_IterBBD; }

	inline vector<small_Dragon*> getVecSmallDRG() { return m_VecSmallDRG; }
	inline vector<small_Dragon*>::iterator getIterSmallDRG() { return m_IterSmallDRG; }

	enemyManager();
	~enemyManager();
};

