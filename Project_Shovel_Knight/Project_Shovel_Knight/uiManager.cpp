#include "stdafx.h"
#include "uiManager.h"


HRESULT uiManager::init()
{
	return E_NOTIMPL;
}

void uiManager::release()
{
}

void uiManager::update()
{
}

void uiManager::render(HDC hdc)
{
}

void uiManager::addUIObject(uiObject * pUI)
{
	((uiButton*)pUI)->setDelegate(this);
}

void uiManager::OnClick(uiButton * pSender)
{
}

uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}
