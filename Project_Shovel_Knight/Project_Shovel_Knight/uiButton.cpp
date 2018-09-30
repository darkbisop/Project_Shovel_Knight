#include "stdafx.h"
#include "uiButton.h"


HRESULT uiButton::init(const char * szImageName, float x, float y
	, POINT ptBtnDown, POINT ptBtnUp)
{
	string str = szImageName;
	m_pImg = IMAGEMANAGER->findImage(str);
	m_position.x = x;
	m_position.y = y;

	m_rc = RectMake(m_position.x, m_position.y,
		m_pImg->getWidth(), m_pImg->getHeight());

	m_ptBtnDown = ptBtnDown;
	m_ptBtnUp = ptBtnUp;

	m_state = ButtonState::IDLE;

	return S_OK;
}

void uiButton::update()
{
	// 버튼이 클릭 됐을 때
	if (PtInRect(&m_rc, g_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			m_state = ButtonState::DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)
			&& m_state == ButtonState::DOWN)
		{
			m_state = ButtonState::UP;

			if (m_pDelegate)
				m_pDelegate->OnClick(this);
		}
	}
	else
	{
		m_state = ButtonState::IDLE;
	}
}

void uiButton::render(HDC hdc)
{
	if (m_isHidden)	return;

	switch (m_state)
	{
	case ButtonState::IDLE:
	case ButtonState::UP:
		m_pImg->frameRender(hdc, m_position.x, m_position.y,
			m_ptBtnUp.x, m_ptBtnUp.y);
		break;
	case ButtonState::DOWN:
		m_pImg->frameRender(hdc, m_position.x, m_position.y,
			m_ptBtnDown.x, m_ptBtnDown.y);
		break;
	}

	uiObject::render(hdc);
}

uiButton::uiButton()
{
}


uiButton::~uiButton()
{
}
