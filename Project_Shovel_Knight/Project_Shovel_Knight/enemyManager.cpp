#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++)
	{
		delete (*m_IterBug);
	}
	m_VecBug.clear();
}

void enemyManager::update()
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++)
	{
		(*m_IterBug)->update();
	}
}

void enemyManager::render(HDC hdc)
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++)
	{
		(*m_IterBug)->render(hdc);
	}
}

void enemyManager::setEnemy(int countX, int countY)
{
	for (int i = 0; i < countY; i++)
	{
		for (int j = 0; j < countX; j++)
		{
			enemy* pEnemy;
			pEnemy = new enemy;
			pEnemy->init("image/ufo.bmp", PointMake(130 + 70 * j, 100 + 60 * i));

			// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			m_vecEnemy.push_back(pEnemy);
		}
	}
}

void enemyManager::setBug()
{
	bug* pBug;
	pBug = new bug;
	pBug->init(550, 808);
	m_VecBug.push_back(pBug);

	bug* pBug2;
	pBug2 = new bug;
	pBug2->init(920, 808);
	m_VecBug.push_back(pBug2);

	bug* pBug3;
	pBug3 = new bug;
	pBug3->init(1140, 808);
	m_VecBug.push_back(pBug3);
}

void enemyManager::setTarget(spaceShip * pTarget)
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->setTarget(pTarget);
	}
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
