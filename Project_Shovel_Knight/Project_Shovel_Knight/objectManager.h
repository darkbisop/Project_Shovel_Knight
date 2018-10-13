#pragma once
#include "PileOfRocks.h"
#include "dirtBlock.h"
#include "dirtBlock_Small.h"
#include "bubble.h"
#include "movingFloor.h"
#include "BubleBuble.h"

class objectManager
{
private:

	vector<PileOfRocks*> v_PileOfRocks;
	vector<PileOfRocks*>::iterator m_IterPOR;

	vector<dirtBlock*> v_dirtBlock;
	vector<dirtBlock*>::iterator m_IterDirtBlock;

	vector<dirtBlock_Small*> v_SmallBlock;
	vector<dirtBlock_Small*>::iterator m_IterSmallBlock;

	vector<bubble*>		m_vecBubble;
	vector<bubble*>::iterator	m_iter;

	vector<movingFloor*> v_MovingFloor;
	vector<movingFloor*>::iterator m_IterMoving;

	vector<BubleBuble*> v_BubleBuble;
	vector<BubleBuble*>::iterator m_IterBuble;

	const char* m_szImageName;
	float		m_fRange;
	int			m_nMaxCount;

public:

	HRESULT init();
	HRESULT init(const char* szImageName, float range, int maxCount);
	void release();
	void update();
	void render(HDC hdc);

	void setPileOfRocks();
	void setDirtblock();
	void setSmallBlock();
	void setMovingFloor();
	void setBubleBuble();

	inline vector<PileOfRocks*> getVecPOR() { return v_PileOfRocks; }
	inline vector<PileOfRocks*>::iterator getIterPOR() { return m_IterPOR; }

	inline vector<dirtBlock*> getVecDIRT() { return v_dirtBlock; }
	inline vector<dirtBlock*>::iterator getIterDIRT() { return m_IterDirtBlock; }

	inline vector<dirtBlock_Small*> getVecSmall() { return v_SmallBlock; }
	inline vector<dirtBlock_Small*>::iterator getIterSmall() { return m_IterSmallBlock; }

	inline vector<bubble*> getVecBubble() { return m_vecBubble; }
	inline vector<bubble*>::iterator getIterBuble() { return m_iter; }

	inline vector<movingFloor*> getVecMoving() { return v_MovingFloor; }
	inline vector<movingFloor*>::iterator getIterMoving() { return m_IterMoving; }

	inline vector<BubleBuble*> getVecBB() { return v_BubleBuble; }
	inline vector<BubleBuble*>::iterator getIterBB() { return m_IterBuble; }

	void fire(float x, float y, float angle, float speed);
	void deleteBubble();

	objectManager();
	~objectManager();
};

