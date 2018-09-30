#pragma once
#include "uiObject.h"

class uiButton : public uiObject
{
protected:
	enum ButtonState
	{
		IDLE,
		UP,
		DOWN,
		NUM
	};
	image*	m_pImg;

	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
	ButtonState			m_state;
	
	POINT m_ptBtnDown;
	POINT m_ptBtnUp;

public:
	HRESULT init(const char* szImageName, float x, float y,
		POINT ptBtnDown, POINT ptBtnUp);
	virtual void update() override;
	virtual void render(HDC hdc) override;

	uiButton();
	virtual ~uiButton();
};

