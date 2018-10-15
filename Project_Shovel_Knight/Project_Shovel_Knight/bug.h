#pragma once
#include "enemyInfo.h"

class effectManager;

class bug : public enemyInfo
{
private:
	RECT	m_rcRange;
	RECT	m_tempRc;		// 이펙트 출력을 위한 임의의 RECT 배틀씬에서 충돌처리 할 생각

	int		m_nScalar;
	bool	m_isHitRight;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void dieMove();
	void damage(int damage);
	void moveFrame();
	void dieFrame();
	void frameChange();
	void collide();


	bug();
	~bug();
};

