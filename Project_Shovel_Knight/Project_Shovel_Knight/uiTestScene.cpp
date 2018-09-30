#include "stdafx.h"
#include "uiTestScene.h"
#include "uiObject.h"
#include "uiImageView.h"
#include "uiButton.h"

HRESULT uiTestScene::init()
{
	IMAGEMANAGER->addImage("image/ui/pop.bmp", "image/ui/pop.bmp",
		600, 340);
	IMAGEMANAGER->addImage("image/ui/button.bmp", "image/ui/button.bmp",
		122, 62, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("image/ui/rocket.bmp", "image/ui/rocket.bmp",
		52, 64);

	//setUI(m_pUiPopup_1);
	//setUI(m_pUiPopup_2);
	//setUI(m_pUiPopup_3);

	return S_OK;
}

void uiTestScene::release()
{
	//SAFE_DELETE(pimageview);
	m_pUiPopup->release();
	SAFE_DELETE(m_pUiPopup);
}

void uiTestScene::update()
{
	m_pUiPopup->update();
}

void uiTestScene::render(HDC hdc)
{
	m_pUiPopup->render(hdc);
}

void uiTestScene::setUI()
{
	// 루트 UI 오브젝트
	m_pUiPopup = new uiObject;

	// 배경 이미지
	uiImageView* pImageView = new uiImageView;	// 왜 지역변수일까?
	pImageView->init("image/ui/pop.bmp", 0, 0);
	m_pUiPopup->addChild(pImageView);

	// 버튼 1
	uiButton* pButton = new uiButton;
	pButton->init("image/ui/button.bmp", 50, 50,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton);
	pButton->setDelegate(m_pUiPopup);
	pButton->setTag(0);

	// 버튼 2
	pButton = new uiButton;
	pButton->init("image/ui/button.bmp", 50, 150,
		PointMake(0, 1), PointMake(0, 0));
	m_pUiPopup->addChild(pButton);
	pButton->setDelegate(m_pUiPopup);
	pButton->setTag(1);

	// 확인용 이미지
	pImageView = new uiImageView;
	pImageView->init("image/ui/rocket.bmp", 300, 100);
	m_pUiPopup->addChild(pImageView);
	pImageView->setTag(3);
	//pImageView->setHidden(true);
}

uiTestScene::uiTestScene()
	: m_pUiPopup(NULL)
{
}


uiTestScene::~uiTestScene()
{
}
