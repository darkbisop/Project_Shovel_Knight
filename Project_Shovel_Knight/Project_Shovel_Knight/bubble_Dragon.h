#pragma once
#include "enemyInfo.h"
class objectManager;

enum bubble_dragon
{
	BUBBLEDG_IDLE, BUBBLEDG_ATK, BUBBLEDG_MOVE, BUBBLEDG_HIT, BUBBLEDG_DIE
};
class bubble_Dragon : public enemyInfo
{
private:
	RECT	m_rc_Head;
	RECT	m_rc_Body;

	objectManager*	m_pBubbleMgr;
	bubble_dragon bubbleDG_state;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void damage(int damage);
	void fire();
	void frameCount();
	void dieEffect();

	inline RECT getHead() { return m_rc_Head; }
	inline RECT getBody() { return m_rc_Body; }

	inline int getLife() { return m_nLife; }
	inline objectManager* getOBJMgr() { return m_pBubbleMgr; }

	bubble_Dragon();
	~bubble_Dragon();
};

