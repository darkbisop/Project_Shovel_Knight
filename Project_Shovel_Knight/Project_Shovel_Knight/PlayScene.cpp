#include "stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init(void)
{
	/*_empty = IMAGEMANAGER->addImage("MainCamera", "image/Empty.bmp", 7200, 1400, true, RGB(255, 0, 255));
	BackGround_Castle = IMAGEMANAGER->addImage("Background_Castle", "image/BackGround/Background_Castle.bmp", 2500, 176, true, RGB(255, 0, 255));
	Back_3_Ground = IMAGEMANAGER->addImage("Back_3_Ground", "image/BackGround/Back_3_Ground.bmp", 1000, 108, true, RGB(255, 0, 255));
	Back_2_Ground = IMAGEMANAGER->addImage("Back_2_Ground", "image/BackGround/Back_2_Ground.bmp", 1000, 176, true, RGB(255, 0, 255));
	Back_Ground = IMAGEMANAGER->addImage("Back_Ground", "image/BackGround/Back_Ground.bmp", 2500, 199, true, RGB(255, 0, 255));
	m_SkyBg = IMAGEMANAGER->addImage("SkyBG", "image/BackGround/Sky.bmp", 399, 208, true, RGB(255, 0, 255));*/

	SOUNDMANAGER->addSound("게임배경음", "Sound/Strike the Earth.mp3", true, true);
	MAPMANAGER->init();
	//SOUNDMANAGER->play("게임배경음", 0.9f);

	/*m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->init();
	m_pEnemyMgr->setBug();*/

	return S_OK;
}

void PlayScene::release(void)
{
	//SAFE_DELETE(m_pEnemyMgr);
}

void PlayScene::update(void)
{
	MAPMANAGER->update();
	//m_pEnemyMgr->update();
}

void PlayScene::render(HDC hdc)
{
	MAPMANAGER->render(hdc);
	//DrawMap();
	MAPMANAGER->CurrMap();
	//m_pEnemyMgr->render(_empty->getMemDC());
}


void PlayScene::DrawMap()
{
	/*m_SkyBg->render(_empty->getMemDC(), (int)MAPMANAGER->getCamera().x, (int)MAPMANAGER->getCamera().y);
	if (MAPMANAGER->getMapNum() == 0 || MAPMANAGER->getMapNum() == 1) {
		BackGround_Castle->loopRender(_empty->getMemDC(), &RectMake(0, 634, 2500, 176), -(int)MAPMANAGER->getCamera().x * 0.8f, 0);
		Back_3_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 714, 2500, 108), -(int)MAPMANAGER->getCamera().x * 0.8f, 0);
		Back_2_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 648, 2500, 176), -(int)MAPMANAGER->getCamera().x * 0.5f, 0);
		Back_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 666, 2500, 199), -(int)MAPMANAGER->getCamera().x * 0.3f, 0);
	}

	if (MAPMANAGER->getMapOn(0) == true) IMAGEMANAGER->findImage("MainRunMap")->render(_empty->getMemDC(), 0, 646);
	if (MAPMANAGER->getMapOn(1) == true) IMAGEMANAGER->findImage("MainRunMap2")->render(_empty->getMemDC(), 1600, 646);
	if (MAPMANAGER->getMapOn(2) == true) IMAGEMANAGER->findImage("MainRunMap3")->render(_empty->getMemDC(), 2000, 646);
	if (MAPMANAGER->getMapOn(3) == true) IMAGEMANAGER->findImage("MainRunMap4")->render(_empty->getMemDC(), 2000, 438);
	if (MAPMANAGER->getMapOn(4) == true) IMAGEMANAGER->findImage("MainRunMap5")->render(_empty->getMemDC(), 2400, 438);
	if (MAPMANAGER->getMapOn(5) == true) IMAGEMANAGER->findImage("MainRunMap6")->render(_empty->getMemDC(), 2800, 438);
	if (MAPMANAGER->getMapOn(6) == true) IMAGEMANAGER->findImage("MainRunMap7")->render(_empty->getMemDC(), 2800, 646);
	if (MAPMANAGER->getMapOn(7) == true) IMAGEMANAGER->findImage("MainRunMap8")->render(_empty->getMemDC(), 2800, 854);
	if (MAPMANAGER->getMapOn(8) == true) IMAGEMANAGER->findImage("MainRunMap9")->render(_empty->getMemDC(), 2800, 1062);
	if (MAPMANAGER->getMapOn(9) == true) IMAGEMANAGER->findImage("MainRunMap10")->render(_empty->getMemDC(), 2400, 1062);
	if (MAPMANAGER->getMapOn(10) == true) IMAGEMANAGER->findImage("MainRunMap11")->render(_empty->getMemDC(), 3200, 1062);
	if (MAPMANAGER->getMapOn(13) == true) IMAGEMANAGER->findImage("MainRunMap14")->render(_empty->getMemDC(), 4000, 854);
	if (MAPMANAGER->getMapOn(14) == true) IMAGEMANAGER->findImage("MainRunMap15")->render(_empty->getMemDC(), 4400, 854);
	if (MAPMANAGER->getMapOn(15) == true) IMAGEMANAGER->findImage("MainRunMap16")->render(_empty->getMemDC(), 4000, 646);
	if (MAPMANAGER->getMapOn(16) == true) IMAGEMANAGER->findImage("MainRunMap17")->render(_empty->getMemDC(), 4000, 438);
	if (MAPMANAGER->getMapOn(17) == true) IMAGEMANAGER->findImage("MainRunMap18")->render(_empty->getMemDC(), 4400, 438);
	if (MAPMANAGER->getMapOn(18) == true) IMAGEMANAGER->findImage("MainRunMap19")->render(_empty->getMemDC(), 5200, 438);
	if (MAPMANAGER->getMapOn(19) == true) IMAGEMANAGER->findImage("MainRunMap20")->render(_empty->getMemDC(), 5600, 438);
	if (MAPMANAGER->getMapOn(20) == true) IMAGEMANAGER->findImage("MainRunMap21")->render(_empty->getMemDC(), 5600, 230);
	if (MAPMANAGER->getMapOn(21) == true) IMAGEMANAGER->findImage("MainRunMap22")->render(_empty->getMemDC(), 5600, 22);
	if (MAPMANAGER->getMapOn(22) == true) IMAGEMANAGER->findImage("MainRunMap23")->render(_empty->getMemDC(), 6000, 22);
	if (MAPMANAGER->getMapOn(23) == true) IMAGEMANAGER->findImage("MainRunMap24")->render(_empty->getMemDC(), 6400, 22);*/
}

PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}
