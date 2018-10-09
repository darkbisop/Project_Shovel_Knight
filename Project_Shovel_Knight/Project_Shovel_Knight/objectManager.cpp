#include "stdafx.h"
#include "objectManager.h"


HRESULT objectManager::init()
{
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

	// vector 자체를 삭제한다
	v_PileOfRocks.clear();
	v_dirtBlock.clear();
}

void objectManager::update()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++) {
		(*m_IterPOR)->update();
	}
	for (m_IterDirtBlock = v_dirtBlock.begin(); m_IterDirtBlock != v_dirtBlock.end(); m_IterDirtBlock++) {
		(*m_IterDirtBlock)->update();
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

	if (MAPMANAGER->getMapNum() == 1) {
		dirtBlock* pdirt4;
		pdirt4 = new dirtBlock;
		pdirt4->init(1697, 758);
		v_dirtBlock.push_back(pdirt4);

		for (int i = 0; i < 2; i++) {
			dirtBlock* pdirt3;
			pdirt3 = new dirtBlock;
			pdirt3->init(1792, 758 - i * 32);
			v_dirtBlock.push_back(pdirt3);
		}
	}
}

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}
