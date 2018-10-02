#include "stdafx.h"
#include "PlayScene.h"


HRESULT PlayScene::init(void)
{
	SOUNDMANAGER->addSound("게임배경음", "Sound/Strike the Earth.mp3", true, true);
	MAPMANAGER->init();
	SOUNDMANAGER->play("게임배경음", 0.9f);
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
