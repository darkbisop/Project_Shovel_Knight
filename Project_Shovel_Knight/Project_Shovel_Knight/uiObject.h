#pragma once
//#include "uiButton.h"
class uiButton;

class iButtonDelegate
{
public:
	virtual void OnClick(uiButton* pSender) = 0;
};

// 모든 ui 클래스의 기본 클래스
// 모든 ui의 공통 특성을 정의한다
class uiObject : public iButtonDelegate
{
protected:
	vector<uiObject*>	m_vecChild;
	vector<uiObject*>::iterator	m_iter;

	RECT		m_rc;

	SYNTHESIZE(int, m_nTag, Tag);
	SYNTHESIZE(FPOINT, m_position, Position);
	SYNTHESIZE(uiObject*, m_pParent, Parent);
	SYNTHESIZE(bool, m_isHidden, Hidden);

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void addChild(uiObject* pChild);

	virtual void OnClick(uiButton* pSender) override;

	uiObject();
	virtual ~uiObject();
};

