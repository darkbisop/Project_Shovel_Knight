#include "stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init(void)
{
	bg = IMAGEMANAGER->addImage("tempsky", "image/BackGround/Sky.bmp", 399, 208, true, RGB(255, 0, 255));
	m_Shop = new Shop;
	m_Shop->init();

	PLAYER->init();

	m_Shop->setInventoryLink(PLAYER->getInventory());
	
	return S_OK;
}

void ShopScene::release(void)
{
	m_Shop->release();
	SAFE_DELETE(m_Shop);
}

void ShopScene::update(void)
{
	m_Shop->update();
	PLAYER->update();

	if (KEYMANAGER->isOnceKeyDown('1')) {
		PLAYER->SetPlayerX(30);
		PLAYER->SetPlayerY(730);
		SCENEMANAGER->changeScene("PlayScene");
	}
}

void ShopScene::render(HDC hdc)
{
	bg->render(hdc);
	m_Shop->render(hdc);
	PLAYER->render(hdc);
}

ShopScene::ShopScene()
{
}


ShopScene::~ShopScene()
{
}
