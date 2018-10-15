#pragma once
#include "enemyInfo.h"

class effectManager;

class bug : public enemyInfo
{
private:
	RECT	m_rcRange;
	RECT	m_tempRc;		// ����Ʈ ����� ���� ������ RECT ��Ʋ������ �浹ó�� �� ����

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

