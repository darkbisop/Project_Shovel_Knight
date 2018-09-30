#include "stdafx.h"
#include "uiObject.h"
#include "uiButton.h"

HRESULT uiObject::init()
{
	return S_OK;
}

void uiObject::release()
{
	m_iter = m_vecChild.begin();
	for (; m_iter != m_vecChild.end(); m_iter++)
	{
		(*m_iter)->release();
		SAFE_DELETE((*m_iter));
	}
	m_vecChild.clear();
}

void uiObject::update()
{
	if (m_isHidden)	return;

	// TODO : ui update

	m_iter = m_vecChild.begin();
	for(; m_iter != m_vecChild.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void uiObject::render(HDC hdc)
{
	if (m_isHidden)	return;

	// TODO : ui render

	m_iter = m_vecChild.begin();
	for (; m_iter != m_vecChild.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void uiObject::addChild(uiObject * pChild)
{
	pChild->setParent(this);
	m_vecChild.push_back(pChild);
}

void uiObject::OnClick(uiButton * pSender)
{
	// 이미지 숨기는 버튼
	if (pSender->getTag() == 0)
	{
		for (auto child : m_vecChild)
		{
			if (child->getTag() == 3)
			{
				child->setHidden(true);
				break;
			}
		}
	}
	// 이미지를 보여주는 버튼
	else if (pSender->getTag() == 1)
	{
		for (auto child : m_vecChild)
		{
			if (child->getTag() == 3)
			{
				child->setHidden(false);
				break;
			}
		}
	}
}

//void uiObject::OnClick(uiButton * pSender)
//{
//
//}

uiObject::uiObject()
	: m_isHidden(false)
	, m_nTag(0)
	, m_pParent(NULL)
{
	m_position.x = 0;
	m_position.y = 0;

	m_rc = { 0, 0 };
}


uiObject::~uiObject()
{
}
