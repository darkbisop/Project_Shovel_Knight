#pragma once
#include "PileOfRocks.h"

class objectManager
{
private:

	vector<PileOfRocks*> v_PileOfRocks;
	vector<PileOfRocks*>::iterator m_IterPOR;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setPileOfRocks();

	inline vector<PileOfRocks*> getVecPOR() { return v_PileOfRocks; }
	inline vector<PileOfRocks*>::iterator getIterPOR() { return m_IterPOR; }

	objectManager();
	~objectManager();
};

