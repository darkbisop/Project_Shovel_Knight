#pragma once
#include <vector>
#include "bullet.h"

class bulletManager
{
private:
	vector<bullet*>	m_vecBullet;
	vector<bullet*>::iterator	m_iter;

	const char* m_szImageName;
	float		m_fRange;
	int			m_nMaxCount;

public:
	HRESULT init(const char* szImageName, float range, int maxCount);
	void release();
	void update();
	void render(HDC hdc);

	void fire(float x, float y, float angle, float speed, int currFrameY);
	void move();

	inline std::vector<bullet*> getVecBullet()
	{
		return m_vecBullet;
	}
	bulletManager();
	~bulletManager();
};

