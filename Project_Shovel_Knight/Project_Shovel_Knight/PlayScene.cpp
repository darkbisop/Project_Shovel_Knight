#include "stdafx.h"
#include "PlayScene.h"


HRESULT PlayScene::init(void)
{
	SOUNDMANAGER->addSound("���ӹ����", "Sound/Strike the Earth.mp3", true, true);
	MAPMANAGER->init();
	SOUNDMANAGER->play("���ӹ����", 0.9f);
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
