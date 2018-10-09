#include "stdafx.h"
#include "objectManager.h"


HRESULT objectManager::init()
{
	return S_OK;
}

HRESULT objectManager::init(const char * szImageName, float range, int maxCount)
{
	m_fRange = range;
	m_nMaxCount = maxCount;
	m_szImageName = szImageName;

	m_vecBubble.reserve(m_nMaxCount);

	return S_OK;
}

void objectManager::release()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++) {
		delete (*m_IterPOR);
	}

	for (m_IterDirtBlock = v_dirtBlock.begin(); m_IterDirtBlock != v_dirtBlock.end(); m_IterDirtBlock++) {
		delete (*m_IterDirtBlock);
	}

	for (m_iter = m_vecBubble.begin();
		m_iter != m_vecBubble.end(); m_iter++)
	{
		delete (*m_iter);
	}

	v_PileOfRocks.clear();
	v_dirtBlock.clear();
	m_vecBubble.clear();
}

void objectManager::update()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++) {
		(*m_IterPOR)->update();
	}
	for (m_IterDirtBlock = v_dirtBlock.begin(); m_IterDirtBlock != v_dirtBlock.end(); m_IterDirtBlock++) {
		(*m_IterDirtBlock)->update();
	}
	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end(); m_iter++) {
		(*m_iter)->update();
	}
}

void objectManager::render(HDC hdc)
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++) {
		(*m_IterPOR)->render(hdc);
	}
	for (m_IterDirtBlock = v_dirtBlock.begin(); m_IterDirtBlock != v_dirtBlock.end(); m_IterDirtBlock++) {
		(*m_IterDirtBlock)->render(hdc);
	}
	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end(); m_iter++) {
		(*m_iter)->render(hdc);
	}
}

void objectManager::setPileOfRocks()
{
	PileOfRocks* pPOR;
	pPOR = new PileOfRocks;
	pPOR->init(400, 808);
	v_PileOfRocks.push_back(pPOR);

	PileOfRocks* pPOR2;
	pPOR2 = new PileOfRocks;
	pPOR2->init(900, 808);
	v_PileOfRocks.push_back(pPOR2);
}

void objectManager::setDirtblock()
{
	// 0���� ������Ʈ
	if (MAPMANAGER->getMapNum() == 0) {
		dirtBlock* pdirt;
		pdirt = new dirtBlock;
		pdirt->init(890, 726);
		v_dirtBlock.push_back(pdirt);

		dirtBlock* pdirt2;
		pdirt2 = new dirtBlock;
		pdirt2->init(1168, 710);
		v_dirtBlock.push_back(pdirt2);

		for (int i = 0; i < 3; i++) {
			dirtBlock* pdirt3;
			pdirt3 = new dirtBlock;
			pdirt3->init(1556, 758 - i * 32);
			v_dirtBlock.push_back(pdirt3);
		}
	}

	// 1���� ������Ʈ
	if (MAPMANAGER->getMapNum() == 1) {
		dirtBlock* pdirt;
		pdirt = new dirtBlock;
		pdirt->init(1697, 758);
		v_dirtBlock.push_back(pdirt);

		for (int i = 0; i < 2; i++) {
			dirtBlock* pdirt;
			pdirt = new dirtBlock;
			pdirt->init(1792, 758 - i * 32);
			v_dirtBlock.push_back(pdirt);
		}
	}

	// 4���� ������Ʈ
	if (MAPMANAGER->getMapOn(4)) {
		dirtBlock* pdirt;
		pdirt = new dirtBlock;
		pdirt->init(2448, 582);
		v_dirtBlock.push_back(pdirt);

		dirtBlock* pdirt2;
		pdirt2 = new dirtBlock;
		pdirt2->init(2750, 582);
		v_dirtBlock.push_back(pdirt2);
	}
}

void objectManager::fire(float x, float y, float angle, float speed)
{
	bubble*	pBubble = new bubble;
	pBubble->init(m_szImageName, speed, x, y, angle, RANDOM->getFromIntTo(40, 95));
	m_vecBubble.push_back(pBubble);

	pBubble->fire(x, y);
}

void objectManager::deleteBubble()
{
	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end();) {
		if ((*m_iter)->getY() < 100) {
			m_iter = m_vecBubble.erase(m_iter);
		}
		else m_iter++;
	}
}

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}
