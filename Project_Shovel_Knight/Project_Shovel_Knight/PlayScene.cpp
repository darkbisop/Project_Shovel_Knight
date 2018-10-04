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
