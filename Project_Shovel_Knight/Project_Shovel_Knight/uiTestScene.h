#pragma once
#include "scene.h"
#include "uiButton.h"

class uiObject;
class uiTestScene : public scene// , public iButtonDelegate
{
protected:
	uiObject * m_pUiPopup;
	uiObject * m_pUiPopup_1;
	uiObject * m_pUiPopup_2;
	uiObject * m_pUiPopup_3;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setUI();

	uiTestScene();
	virtual ~uiTestScene();
};

