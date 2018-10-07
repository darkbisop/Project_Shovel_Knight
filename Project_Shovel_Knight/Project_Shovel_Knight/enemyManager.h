#pragma once
#include <vector>
#include "enemy.h"
#include "bug.h"

class enemyManager
{
private:
	
	std::vector<enemy*>	m_vecEnemy;
	std::vector<enemy*>::iterator	m_iter;

	vector<bug*> m_VecBug;
	vector<bug*>::iterator m_IterBug;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setBug();
	void setTarget(spaceShip* pTarget);

	
	inline std::vector<enemy*> getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }

	inline std::vector<bug*> getVecBug() { return m_VecBug; }
	inline std::vector<bug*>::iterator getIterBug() { return m_IterBug; }

	enemyManager();
	~enemyManager();
};

