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
	PlayerMapCollision();
}

void PlayScene::render(HDC hdc)
{
	MAPMANAGER->render(hdc);
}

void PlayScene::PlayerMapCollision()
{
	for (int i = 0; i < MAPMANAGER->getMapVectorRcSize(); i++)
	{
		PLAYER->RectColliosion(MAPMANAGER->getMapVectorRc(i));

		/*if (MAPMANAGER->getMapNum() == 1 && MAPMANAGER->getMapVectorRcSize() > 2) {
			MAPMANAGER->EraseRect(i);
		}*/
	}
}

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}
