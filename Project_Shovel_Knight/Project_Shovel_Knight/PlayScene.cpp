#include "stdafx.h"
#include "PlayScene.h"


HRESULT PlayScene::init(void)
{
	MAPMANAGER->init();

	return S_OK;
}

void PlayScene::release(void)
{
}

void PlayScene::update(void)
{
	MAPMANAGER->update();
}

void PlayScene::render(HDC hdc)
{
	MAPMANAGER->render(hdc);
}

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}
