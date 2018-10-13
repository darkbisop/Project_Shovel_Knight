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

	for (m_IterSmallBlock = v_SmallBlock.begin(); m_IterSmallBlock != v_SmallBlock.end(); m_IterSmallBlock++) {
		delete (*m_IterSmallBlock);
	}

	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end(); m_iter++) {
		delete (*m_iter);
	}

	for (m_IterMoving = v_MovingFloor.begin(); m_IterMoving != v_MovingFloor.end(); m_IterMoving++) {
		delete (*m_IterMoving);
	}

	for (m_IterBuble = v_BubleBuble.begin(); m_IterBuble != v_BubleBuble.end(); m_IterBuble++) {
		delete (*m_IterBuble);
	}

	v_PileOfRocks.clear();
	v_dirtBlock.clear();
	v_SmallBlock.clear();
	m_vecBubble.clear();
	v_MovingFloor.clear();
	v_BubleBuble.clear();
}

void objectManager::update()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++) {
		(*m_IterPOR)->update();
	}
	for (m_IterDirtBlock = v_dirtBlock.begin(); m_IterDirtBlock != v_dirtBlock.end(); m_IterDirtBlock++) {
		(*m_IterDirtBlock)->update();
	}
	for (m_IterSmallBlock = v_SmallBlock.begin(); m_IterSmallBlock != v_SmallBlock.end(); m_IterSmallBlock++) {
		(*m_IterSmallBlock)->update();
	}
	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end(); m_iter++) {
		(*m_iter)->update();
	}
	for (m_IterMoving = v_MovingFloor.begin(); m_IterMoving != v_MovingFloor.end(); m_IterMoving++) {
		(*m_IterMoving)->update();
	}
	for (m_IterBuble = v_BubleBuble.begin(); m_IterBuble != v_BubleBuble.end(); m_IterBuble++) {
		(*m_IterBuble)->update();
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
	for (m_IterSmallBlock = v_SmallBlock.begin(); m_IterSmallBlock != v_SmallBlock.end(); m_IterSmallBlock++) {
		(*m_IterSmallBlock)->render(hdc);
	}
	for (m_iter = m_vecBubble.begin(); m_iter != m_vecBubble.end(); m_iter++) {
		(*m_iter)->render(hdc);
	}
	for (m_IterMoving = v_MovingFloor.begin(); m_IterMoving != v_MovingFloor.end(); m_IterMoving++) {
		(*m_IterMoving)->render(hdc);
	}
	for (m_IterBuble = v_BubleBuble.begin(); m_IterBuble != v_BubleBuble.end(); m_IterBuble++) {
		(*m_IterBuble)->render(hdc);
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
	// 0번맵 오브젝트
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

	// 1번맵 오브젝트
	if (MAPMANAGER->getMapOn(1)) {

		//v_dirtBlock.erase(v_dirtBlock.begin(), v_dirtBlock.begin() + 5);

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

	// 4번맵 오브젝트
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

	// 7번맵 오브젝트
	if (MAPMANAGER->getMapOn(7)) {
		for (int i = 0; i < 3; i++) {
			dirtBlock* pdirt;
			pdirt = new dirtBlock;
			pdirt->init(3136, 950 + i * 32);
			v_dirtBlock.push_back(pdirt);
		}
	}


	// 10번맵 오브젝트
	if (MAPMANAGER->getMapOn(10)) {
		for (int i = 0; i < 3; i++) {
			dirtBlock* pdirt;
			pdirt = new dirtBlock;
			pdirt->init(3360 + i * 32, 1143 );
			v_dirtBlock.push_back(pdirt);
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				dirtBlock* pdirt;
				pdirt = new dirtBlock;
				pdirt->init(3456 + j * 32, 1175 + i * 32);
				v_dirtBlock.push_back(pdirt);
			}
		}

		dirtBlock* pdirt;
		pdirt = new dirtBlock;
		pdirt->init(3628, 1206);
		v_dirtBlock.push_back(pdirt);

		dirtBlock* pdirt2;
		pdirt2 = new dirtBlock;
		pdirt2->init(3660, 1174);
		v_dirtBlock.push_back(pdirt2);

		dirtBlock* pdirt3;
		pdirt3 = new dirtBlock;
		pdirt3->init(3724, 1206);
		v_dirtBlock.push_back(pdirt3);

		dirtBlock* pdirt4;
		pdirt4 = new dirtBlock;
		pdirt4->init(3788, 1206);
		v_dirtBlock.push_back(pdirt4);
	}
}

void objectManager::setSmallBlock()
{
	// 4번맵 오브젝트
	if (MAPMANAGER->getMapOn(4)) {
		dirtBlock_Small* pSmall;
		pSmall = new dirtBlock_Small;
		pSmall->init(2448, 566);
		v_SmallBlock.push_back(pSmall);

		dirtBlock_Small* pSmall2;
		pSmall2 = new dirtBlock_Small;
		pSmall2->init(2734, 598);
		v_SmallBlock.push_back(pSmall2);
	}


	// 6번맵 오브젝트
	if (MAPMANAGER->getMapOn(6)) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				dirtBlock_Small* pSmall;
				pSmall = new dirtBlock_Small;
				pSmall->init(2832 + j * 16, 791 + i * 16);
				v_SmallBlock.push_back(pSmall);
			}
		}
	}

	// 10번맵 오브젝트
	if (MAPMANAGER->getMapOn(10)) {
		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3596 + i * 16, 1222);
			v_SmallBlock.push_back(pSmall);
		}

		dirtBlock_Small* pSmall;
		pSmall = new dirtBlock_Small;
		pSmall->init(3612 , 1206);
		v_SmallBlock.push_back(pSmall);

		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3628 + i * 16, 1190);
			v_SmallBlock.push_back(pSmall);
		}

		dirtBlock_Small* pSmall2;
		pSmall2 = new dirtBlock_Small;
		pSmall2->init(3644, 1174);
		v_SmallBlock.push_back(pSmall2);

		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3660 + i * 16, 1158);
			v_SmallBlock.push_back(pSmall);
		}

		dirtBlock_Small* pSmall3;
		pSmall3 = new dirtBlock_Small;
		pSmall3->init(3676 , 1142);
		v_SmallBlock.push_back(pSmall3);


		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3708 , 1206 + i * 16);
			v_SmallBlock.push_back(pSmall);
		}

		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3756, 1206 + i * 16);
			v_SmallBlock.push_back(pSmall);
		}

		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3772, 1206 + i * 16);
			v_SmallBlock.push_back(pSmall);
		}

		for (int i = 0; i < 2; i++) {
			dirtBlock_Small* pSmall;
			pSmall = new dirtBlock_Small;
			pSmall->init(3820, 1206 + i * 16);
			v_SmallBlock.push_back(pSmall);
		}



		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				dirtBlock_Small* pSmall;
				pSmall = new dirtBlock_Small;
				pSmall->init(3692 + j * 16, 1142 + i * 16);
				v_SmallBlock.push_back(pSmall);
			}
		}
	}


	// 20번맵 오브젝트
	if (MAPMANAGER->getMapOn(20)) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				dirtBlock_Small* pSmall;
				pSmall = new dirtBlock_Small;
				pSmall->init(5824 + j * 16, 295 + i * 16);
				v_SmallBlock.push_back(pSmall);
			}
		}
	}
}

void objectManager::setMovingFloor()
{
	if (MAPMANAGER->getMapOn(3)) {
		movingFloor* pMoving;
		pMoving = new movingFloor;
		pMoving->init(2190, 526, 160, 1, true, false, true, false, 1.5f);
		v_MovingFloor.push_back(pMoving);
	}

	if (MAPMANAGER->getMapOn(4)) {
		movingFloor* pMoving;
		pMoving = new movingFloor;
		pMoving->init(2608, 622, 160, 1, true, false, true, false, 1.5f);
		v_MovingFloor.push_back(pMoving);
	}

	if (MAPMANAGER->getMapOn(13)) {
		movingFloor* pMoving;
		pMoving = new movingFloor;
		pMoving->init(4073, 986, 1, 80, false, true, false, true, 1.0f);
		v_MovingFloor.push_back(pMoving);

		movingFloor* pMoving2;
		pMoving2 = new movingFloor;
		pMoving2->init(4220, 974, 160, 1, true, false, true, false, 1.5f);
		v_MovingFloor.push_back(pMoving2);
	}

	if (MAPMANAGER->getMapOn(17)) {
		movingFloor* pMoving;
		pMoving = new movingFloor;
		pMoving->init(5016, 570, 1, 140, false, true, false, true, 1.0f);
		v_MovingFloor.push_back(pMoving);
	}
}

void objectManager::setBubleBuble()
{
	if (MAPMANAGER->getMapOn(2)) {
		BubleBuble* pbuble;
		pbuble = new BubleBuble;
		pbuble->init(2176, 800, 100, true);
		v_BubleBuble.push_back(pbuble);
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
