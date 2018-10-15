#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++) {
		delete (*m_IterBug);
	}
	for (m_IterBBD = m_VecBBD.begin(); m_IterBBD != m_VecBBD.end(); m_IterBBD++) {
		delete (*m_IterBBD);
	}
	for (m_IterSmallDRG = m_VecSmallDRG.begin(); m_IterSmallDRG != m_VecSmallDRG.end(); m_IterSmallDRG++) {
		delete (*m_IterSmallDRG);
	}
	m_VecBug.clear();
	m_VecBBD.clear();
	m_VecSmallDRG.clear();
}

void enemyManager::update()
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++) {
		(*m_IterBug)->update();
	}
	for (m_IterBBD = m_VecBBD.begin(); m_IterBBD != m_VecBBD.end(); m_IterBBD++) {
		(*m_IterBBD)->update();
	}
	for (m_IterSmallDRG = m_VecSmallDRG.begin(); m_IterSmallDRG != m_VecSmallDRG.end(); m_IterSmallDRG++) {
		(*m_IterSmallDRG)->update();
	}
}

void enemyManager::render(HDC hdc)
{
	for (m_IterBug = m_VecBug.begin(); m_IterBug != m_VecBug.end(); m_IterBug++){
		(*m_IterBug)->render(hdc);
	}
	for (m_IterBBD = m_VecBBD.begin(); m_IterBBD != m_VecBBD.end(); m_IterBBD++) {
		(*m_IterBBD)->render(hdc);
	}
	for (m_IterSmallDRG = m_VecSmallDRG.begin(); m_IterSmallDRG != m_VecSmallDRG.end(); m_IterSmallDRG++) {
		(*m_IterSmallDRG)->render(hdc);
	}
}


void enemyManager::setBug()
{
	if (MAPMANAGER->getMapNum() == 0) {
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

	if (MAPMANAGER->getMapNum() == 1) {
		bug* pBug4;
		pBug4 = new bug;
		pBug4->init(1850, 808);
		m_VecBug.push_back(pBug4);
	}

	if (MAPMANAGER->getMapOn(3)) {
		bug* pBug;
		pBug = new bug;
		pBug->init(2347, 504);
		m_VecBug.push_back(pBug);
	}
}

void enemyManager::setBubleDragon()
{
	if (MAPMANAGER->getMapOn(5)) {
		bubble_Dragon* pBBD;
		pBBD = new bubble_Dragon;
		pBBD->init(2970, 528);
		m_VecBBD.push_back(pBBD);
	}

	if (MAPMANAGER->getMapOn(18)) {
		bubble_Dragon* pBBD;
		pBBD = new bubble_Dragon;
		pBBD->init(5374, 546);
		m_VecBBD.push_back(pBBD);
	}
}

void enemyManager::setSmallDragon()
{
	if (MAPMANAGER->getMapOn(10)) {
		small_Dragon* pSMD;
		pSMD = new small_Dragon;
		pSMD->init(3575, 1130, smallDG_CIRCLE);
		m_VecSmallDRG.push_back(pSMD);
	}

	if (MAPMANAGER->getMapOn(13)) {
		small_Dragon* pSMD;
		pSMD = new small_Dragon;
		pSMD->init(4110, 950, smallDG_CIRCLE);
		m_VecSmallDRG.push_back(pSMD);
	}

	if (MAPMANAGER->getMapOn(15)) {
		small_Dragon* pSMD;
		pSMD = new small_Dragon;
		pSMD->init(4060, 705, smallDG_UPDOWN);
		m_VecSmallDRG.push_back(pSMD);
	}
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
