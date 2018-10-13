#include "stdafx.h"
#include "ShopScene.h"


HRESULT ShopScene::init(void)
{

	return S_OK;
}

void ShopScene::release(void)
{
	
}

void ShopScene::update(void)
{
	
	//PLAYER->update();

	if (KEYMANAGER->isOnceKeyDown('1')) {
		PLAYER->SetPlayerX(-30);
		PLAYER->SetPlayerY(790);
		SCENEMANAGER->changeScene("PlayScene");
		PLAYER->setAppear(true);
	}
}

void ShopScene::render(HDC hdc)
{
	
}

ShopScene::ShopScene()
{
}


ShopScene::~ShopScene()
{
}
