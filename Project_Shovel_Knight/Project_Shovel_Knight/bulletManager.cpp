#include "stdafx.h"
#include "bulletManager.h"


HRESULT bulletManager::init(const char * szImageName, float range, int maxCount)
{
	m_fRange = range;
	m_nMaxCount = maxCount;
	m_szImageName = szImageName;

	m_vecBullet.reserve(m_nMaxCount);

	return S_OK;
}

void bulletManager::release()
{
	for (m_iter = m_vecBullet.begin();
		m_iter != m_vecBullet.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecBullet.clear();
}

void bulletManager::update()
{
	for (m_iter = m_vecBullet.begin();
		m_iter != m_vecBullet.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void bulletManager::render(HDC hdc)
{
	for (m_iter = m_vecBullet.begin();
		m_iter != m_vecBullet.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void bulletManager::fire(float x, float y, float angle, float speed, int currFrameY)
{
	bullet*	pBullet = new bullet;

	pBullet->init(m_szImageName, speed, x, y, angle, 300, currFrameY);
	m_vecBullet.push_back(pBullet);

	pBullet->fire(x, y);
}

void bulletManager::move()
{
}

bulletManager::bulletManager()
{
}


bulletManager::~bulletManager()
{
}
