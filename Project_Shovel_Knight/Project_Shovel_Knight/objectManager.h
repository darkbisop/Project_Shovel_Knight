#pragma once
#include "PileOfRocks.h"
#include "dirtBlock.h"

class objectManager
{
private:

	vector<PileOfRocks*> v_PileOfRocks;
	vector<PileOfRocks*>::iterator m_IterPOR;

	vector<dirtBlock*> v_dirtBlock;
	vector<dirtBlock*>::iterator m_IterDirtBlock;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setPileOfRocks();
	void setDirtblock();

	inline vector<PileOfRocks*> getVecPOR() { return v_PileOfRocks; }
	inline vector<PileOfRocks*>::iterator getIterPOR() { return m_IterPOR; }

	inline vector<dirtBlock*> getVecDIRT() { return v_dirtBlock; }
	inline vector<dirtBlock*>::iterator getIterDIRT() { return m_IterDirtBlock; }

	objectManager();
	~objectManager();
};

