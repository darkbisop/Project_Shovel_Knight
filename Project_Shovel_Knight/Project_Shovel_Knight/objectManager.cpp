#include "stdafx.h"
#include "objectManager.h"


HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++)
	{
		delete (*m_IterPOR);
	}
	// vector 자체를 삭제한다
	v_PileOfRocks.clear();
}

void objectManager::update()
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++)
	{
		(*m_IterPOR)->update();
	}
}

void objectManager::render(HDC hdc)
{
	for (m_IterPOR = v_PileOfRocks.begin(); m_IterPOR != v_PileOfRocks.end(); m_IterPOR++)
	{
		(*m_IterPOR)->render(hdc);
	}
}

void objectManager::setPileOfRocks()
{
	PileOfRocks* pPOR;
	pPOR = new PileOfRocks;
	pPOR->init(450, 809);
	v_PileOfRocks.push_back(pPOR);
}

objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}
