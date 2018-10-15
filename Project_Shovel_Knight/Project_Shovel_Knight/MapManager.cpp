#include "stdafx.h"
#include "MapManager.h"
#include "MapImage.h"
#include "enemyManager.h"
#include "effectManager.h"
#include "objectManager.h"
#include "animation.h"

HRESULT MapManager::init(void)
{
	_empty = IMAGEMANAGER->addImage("MainCamera", "image/Empty.bmp", 7200, 1400, true, RGB(255, 0, 255));
	BackGround_Castle = IMAGEMANAGER->addImage("Background_Castle", "image/BackGround/Background_Castle.bmp", 2500, 176, true, RGB(255, 0, 255));
	Back_3_Ground = IMAGEMANAGER->addImage("Back_3_Ground", "image/BackGround/Back_3_Ground.bmp", 1000, 108, true, RGB(255, 0, 255));
	Back_2_Ground = IMAGEMANAGER->addImage("Back_2_Ground", "image/BackGround/Back_2_Ground.bmp", 1000, 176, true, RGB(255, 0, 255));
	Back_Ground = IMAGEMANAGER->addImage("Back_Ground", "image/BackGround/Back_Ground.bmp", 2500, 199, true, RGB(255, 0, 255));
	m_pImg = IMAGEMANAGER->addImage("bubble", "image/Enemy/bubble_dragon/bubble_move.bmp", 108, 27, 4, 1, true, RGB(255, 0, 255));
	m_SkyBg = IMAGEMANAGER->addImage("SkyBG", "image/BackGround/Sky.bmp", 399, 208, true, RGB(255, 0, 255));
	m_shopBg = IMAGEMANAGER->addImage("ShopBG", "image/BackGround/Shop.bmp", 400, 208, true, RGB(255, 0, 255));
	m_Screen = IMAGEMANAGER->addImage("ScreenSFX", "image/effect/ScreenSFX.bmp", 3200, 238, 8, 1, true, RGB(255, 0, 255));
	m_ScreenRvs = IMAGEMANAGER->addImage("ScreenSFXRR", "image/effect/ScreenSFX.bmp", 3200, 238, 8, 1, true, RGB(255, 0, 255));
	m_SaveCheckPoint = IMAGEMANAGER->addImage("Check", "image/Object/Check.bmp", 231, 48, 11, 1, true, RGB(255, 0, 255));

	m_pMapImage = new MapImage;
	m_pMapImage->init();

	m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->setBug();
	//m_pEnemyMgr->setBubleDragon();

	m_pObjectMgr = new objectManager;
	m_pObjectMgr->init();
	m_pObjectMgr->setPileOfRocks();
	m_pObjectMgr->setDirtblock();

	PLAYER->init();

	m_Shop = new Shop;
	m_Shop->init();
	m_Shop->setInventoryLink(PLAYER->getInventory());

	//EFFECTMANAGER->addEffect("enemy_effect", "image/effect/enemy_effect.bmp", 120, 16, 24, 16, 10, 10);
	SOUNDMANAGER->addSound("¸¶À»", "Sound/Village.mp3", false, false);

	for (int i = 0; i < 24; i++) {
		MovingCamera[i] = false;
	}

	for (int i = 1; i < 24; i++) {
		MapOn[i] = false;
	}

	CurrMapNum = 100;
	MapOn[11] = true;
	ScreenSFXOn = false;
	ScreenSFXREV2 = false;
	m_ReverseFrameX = 8;
	m_CheckSaveFrame = 0;
	m_screenFrame = 8;

	CheckMapRect();
	PushRect();
	SOUNDMANAGER->play("¸¶À»", 0.9f);

	return S_OK;
}

void MapManager::release(void)
{
	SAFE_DELETE(m_pEnemyMgr);
	SAFE_DELETE(m_pObjectMgr);
	SAFE_DELETE(m_pMapImage)

	m_Shop->release();
	SAFE_DELETE(m_Shop);
}

void MapManager::update(void)
{
	m_Shop->update();
	CollisionCheck_ChangeMapRect();
	MovingMap();
	ScreenEffect();
	m_pEnemyMgr->update();
	m_pObjectMgr->update();
	EFFECTMANAGER->update();
	CollisionObject();
	CollisionEnemy();
	CollisionBoss();
	CollisionMap();
	PLAYER->update();
}

void MapManager::render(HDC hdc)
{

	m_SkyBg->render(_empty->getMemDC(), (int)m_Camera.x , (int)m_Camera.y);
	if (CurrMapNum == 0 || CurrMapNum == 1) {
		BackGround_Castle->loopRender(_empty->getMemDC(), &RectMake(0, 634, 2500, 176), -(int)m_Camera.x * 0.8f, 0);
		Back_3_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 714, 2500, 108), -(int)m_Camera.x * 0.8f, 0);
		Back_2_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 648, 2500, 176), -(int)m_Camera.x * 0.5f, 0);
		Back_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 666, 2500, 199), -(int)m_Camera.x * 0.3f, 0);
	}
	
	if (MapOn[11] == true) m_shopBg->render(_empty->getMemDC(), 0, 12);

	Rectangle(_empty->getMemDC(), CheckChangeMapRect[15].left, CheckChangeMapRect[15].top, CheckChangeMapRect[15].right, CheckChangeMapRect[15].bottom);

	CurrMap();

	for (vIterLDRRC = vLadderRect.begin(); vIterLDRRC != vLadderRect.end(); vIterLDRRC++) {
		Rectangle(_empty->getMemDC(), vIterLDRRC->_rc.left, vIterLDRRC->_rc.top, vIterLDRRC->_rc.right, vIterLDRRC->_rc.bottom);
	}

	m_pObjectMgr->render(_empty->getMemDC());
	m_pEnemyMgr->render(_empty->getMemDC());
	EFFECTMANAGER->render(_empty->getMemDC());
	PLAYER->render(_empty->getMemDC());
	m_Shop->render(_empty->getMemDC());
	if (ScreenSFXOn == true) m_Screen->frameRender(_empty->getMemDC(), m_Camera.x, m_Camera.y, m_CurrFrameX, 0);
	if (ScreenSFXREV == true) m_Screen->frameRender(_empty->getMemDC(), m_Camera.x, m_Camera.y, m_CurrFrameX, 0);
	if (ScreenSFXREV2 == true) m_Screen->frameRender(_empty->getMemDC(), m_Camera.x, m_Camera.y, m_screenFrame, 0);
	

	for (vIterSaveRC = vSaveRect.begin(); vIterSaveRC != vSaveRect.end(); vIterSaveRC++) {
		//Rectangle(_empty->getMemDC(), vIterSaveRC->_rc.left, vIterSaveRC->_rc.top, vIterSaveRC->_rc.right, vIterSaveRC->_rc.bottom);
		if (SaveCheck == true) m_SaveCheckPoint->frameRender(_empty->getMemDC(), vIterSaveRC->_rc.left - 7, vIterSaveRC->_rc.top - 1, m_CheckSaveFrame, 0);
	}

	//for (vIterSpikeRC = vSpikeRect.begin(); vIterSpikeRC != vSpikeRect.end(); vIterSpikeRC++) {
	//	Rectangle(_empty->getMemDC(), vIterSpikeRC->_rc.left, vIterSpikeRC->_rc.top, vIterSpikeRC->_rc.right, vIterSpikeRC->_rc.bottom);
	//}

	/*for (vIterRC = vRect.begin(); vIterRC != vRect.end(); vIterRC++) {
		Rectangle(_empty->getMemDC(), vIterRC->_rc.left, vIterRC->_rc.top, vIterRC->_rc.right, vIterRC->_rc.bottom);
	}*/

	_empty->render(hdc, 0, 0, m_Camera.x, m_Camera.y, WINSIZEX, WINSIZEY);

	TIMEMANAGER->render(hdc);
	
	//char str[64];
	//for (int i = 0; i < vRect.size(); i++) {
	//	wsprintf(str, "x : %d", vRect.size());
	//	//sprintf_s(str, "x : %f, y : %f", PLAYER->getPlayerX(), PLAYER->getPlayerY());
	//	TextOut(hdc, PLAYER->getPlayerX(), PLAYER->getPlayerY() - 100, str, strlen(str));
	//}
}

void MapManager::CheckMapRect()
{
	CheckChangeMapRect[0] = RectMake(1598, 743, 3, 50);
	CheckChangeMapRect[1] = RectMake(2000, 743, 3, 50);
	CheckChangeMapRect[2] = RectMake(2272, 646, 50, 3);
	CheckChangeMapRect[3] = RectMake(2397, 468, 3, 50);
	CheckChangeMapRect[4] = RectMake(2797, 579, 3, 50);
	CheckChangeMapRect[5] = RectMake(3102, 650, 50, 3);
	CheckChangeMapRect[6] = RectMake(2872, 853, 50, 3);
	CheckChangeMapRect[7] = RectMake(3136, 1062, 50, 3);
	CheckChangeMapRect[8] = RectMake(2800, 1202, 6, 50);
	CheckChangeMapRect[9] = RectMake(3200, 1160, 3, 50);
	CheckChangeMapRect[12] = RectMake(4315, 1071, 50, 3);
	CheckChangeMapRect[13] = RectMake(4400, 920, 3, 50);
	CheckChangeMapRect[14] = RectMake(4000, 857, 50, 3);
	CheckChangeMapRect[15] = RectMake(4090, 641, 50, 3);
	CheckChangeMapRect[16] = RectMake(4265, 641, 50, 3);
	CheckChangeMapRect[17] = RectMake(4400, 497, 3, 50);
	CheckChangeMapRect[18] = RectMake(5197, 477, 3, 50);
	CheckChangeMapRect[19] = RectMake(5600, 560, 3, 50);
	CheckChangeMapRect[20] = RectMake(5930, 440, 50, 3);
	CheckChangeMapRect[21] = RectMake(5724, 230, 50, 3);
	CheckChangeMapRect[22] = RectMake(6000, 160, 3, 50);
	CheckChangeMapRect[23] = RectMake(6398, 160, 3, 50);
	CheckChangeMapRect[24] = RectMake(394, 160, 3, 50);
}

void MapManager::CurrMap()
{
	// 0¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 0 && MovingCamera[0] == false) {

		m_Camera = { (int)PLAYER->getPlayerX() - 180, (int)PLAYER->getPlayerY() };
		
		if (m_Camera.x < 2) m_Camera.x = 2;
		else if (m_Camera.x + WINSIZEX > 1600) m_Camera.x = 1600 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 854) m_Camera.y = 854 - WINSIZEY;
	}

	// 10¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 12 && MovingCamera[11] == false && MovingCamera[12] == false) {

		m_Camera = { (int)PLAYER->getPlayerX() - 180, (int)PLAYER->getPlayerY() };

		if (m_Camera.x < 3200) m_Camera.x = 3200;
		else if (m_Camera.x + WINSIZEX > 4397) m_Camera.x = 4397 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 1270) m_Camera.y = 1270 - WINSIZEY;
	}

	// 14¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 14 && MovingCamera[13] == false && MovingCamera[14] == false) {

		m_Camera = { (int)PLAYER->getPlayerX() - 180, (int)PLAYER->getPlayerY() };
	
		if (m_Camera.x < 4400) m_Camera.x = 4400;
		else if (m_Camera.x + WINSIZEX > 4976) m_Camera.x = 4976 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 1062) m_Camera.y = 1062 - WINSIZEY;
	}

	// 17¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 17 && MovingCamera[16] == false && MovingCamera[17] == false) {

		m_Camera = { (int)PLAYER->getPlayerX() - 180, (int)PLAYER->getPlayerY() };

		if (m_Camera.x < 4400) m_Camera.x = 4400;
		else if (m_Camera.x + WINSIZEX > 5200) m_Camera.x = 5200 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 646) m_Camera.y = 646 - WINSIZEY;
	}

	if (MapOn[0] == true) IMAGEMANAGER->findImage("MainRunMap")->render(_empty->getMemDC(), 0, 646);
	if (MapOn[1] == true) IMAGEMANAGER->findImage("MainRunMap2")->render(_empty->getMemDC(), 1600, 646);
	if (MapOn[2] == true) IMAGEMANAGER->findImage("MainRunMap3")->render(_empty->getMemDC(), 2000, 646);
	if (MapOn[3] == true) IMAGEMANAGER->findImage("MainRunMap4")->render(_empty->getMemDC(), 2000, 438);
	if (MapOn[4] == true) IMAGEMANAGER->findImage("MainRunMap5")->render(_empty->getMemDC(), 2400, 438);
	if (MapOn[5] == true) IMAGEMANAGER->findImage("MainRunMap6")->render(_empty->getMemDC(), 2800, 438);
	if (MapOn[6] == true) IMAGEMANAGER->findImage("MainRunMap7")->render(_empty->getMemDC(), 2800, 646);
	if (MapOn[7] == true) IMAGEMANAGER->findImage("MainRunMap8")->render(_empty->getMemDC(), 2800, 854);
	if (MapOn[8] == true) IMAGEMANAGER->findImage("MainRunMap9")->render(_empty->getMemDC(), 2800, 1062);
	if (MapOn[9] == true) IMAGEMANAGER->findImage("MainRunMap10")->render(_empty->getMemDC(), 2400, 1062);
	if (MapOn[10] == true) IMAGEMANAGER->findImage("MainRunMap11")->render(_empty->getMemDC(), 3200, 1062);
	if (MapOn[13] == true) IMAGEMANAGER->findImage("MainRunMap14")->render(_empty->getMemDC(), 4000, 854);
	if (MapOn[14] == true) IMAGEMANAGER->findImage("MainRunMap15")->render(_empty->getMemDC(), 4400, 854);
	if (MapOn[15] == true) IMAGEMANAGER->findImage("MainRunMap16")->render(_empty->getMemDC(), 4000, 646);
	if (MapOn[16] == true) IMAGEMANAGER->findImage("MainRunMap17")->render(_empty->getMemDC(), 4000, 438);
	if (MapOn[17] == true) IMAGEMANAGER->findImage("MainRunMap18")->render(_empty->getMemDC(), 4400, 438);
	if (MapOn[18] == true) IMAGEMANAGER->findImage("MainRunMap19")->render(_empty->getMemDC(), 5200, 438);
	if (MapOn[19] == true) IMAGEMANAGER->findImage("MainRunMap20")->render(_empty->getMemDC(), 5600, 438);
	if (MapOn[20] == true) IMAGEMANAGER->findImage("MainRunMap21")->render(_empty->getMemDC(), 5600, 230);
	if (MapOn[21] == true) IMAGEMANAGER->findImage("MainRunMap22")->render(_empty->getMemDC(), 5600, 22);
	if (MapOn[22] == true) IMAGEMANAGER->findImage("MainRunMap23")->render(_empty->getMemDC(), 6000, 22);
	if (MapOn[23] == true) IMAGEMANAGER->findImage("MainRunMap24")->render(_empty->getMemDC(), 6400, 22);
}

void MapManager::CollisionCheck_ChangeMapRect()
{
	if (CurrMapNum == 100) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[24])) {
			ScreenSFXOn = true;

			if (ScreenSFXOn && m_CurrFrameX == 8) {
				SOUNDMANAGER->stop("¸¶À»");
				MapOn[0] = true;
				MapOn[11] == false;
				ScreenSFXOn = false;
				CurrMapNum = 0;
				PLAYER->SetPlayerX(-35);
				PLAYER->SetPlayerY(780);
				PushRect();
				ScreenSFXREV = true;
			}
		}
	}

	if (CurrMapNum == 4 && PLAYER->getHP() <= 0) {
		if (ScreenSFXOn && m_CurrFrameX == 8) {
			ScreenSFXREV2 = true;
			LoadPoint();
		}
	}

	// ##### 0 --> 1  #####
	if (CurrMapNum == 0) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[0])) {
			MovingCamera[0] = true;
			MapOn[1] = true;
		}
	}

	// ##### 0 <-- 1  #####
	if (CurrMapNum == 1) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[0])) {
			MovingCamera[0] = true;
			MapOn[0] = true;
		}
	}

	// ##### 1 --> 2 #####
	if (CurrMapNum == 1) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[1])) {
			//MovingCamera[2] = true;
			MovingCamera[1] = true;
			MapOn[2] = true;
		}
	}

	// ##### 1 <-- 2  #####
	if (CurrMapNum == 2) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[1])) {
			MovingCamera[1] = true;
			MapOn[1] = true;
		}
	}

	// ##### 2 --> 3 #####
	if (CurrMapNum == 2) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[2])) {
			//MovingCamera[3] = true;
			MovingCamera[2] = true;
			MapOn[3] = true;
		}
	}

	// ##### 2 <-- 3  #####
	if (CurrMapNum == 3) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[2])) {
			//MovingCamera[3] = true;
			MovingCamera[2] = true;
			MapOn[2] = true;
		}
	}


	// ##### 3 --> 4  #####
	if (CurrMapNum == 3) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[3])) {
			//MovingCamera[4] = true;
			MovingCamera[3] = true;
			MapOn[4] = true;
		}
	}

	// ##### 3 <-- 4  #####
	if (CurrMapNum == 4) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[3])) {
			//MovingCamera[4] = true;
			MovingCamera[3] = true;
			MapOn[3] = true;
		}
	}


	// ##### 4 --> 5  #####
	if (CurrMapNum == 4) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[4])) {
			//MovingCamera[5] = true;
			MovingCamera[4] = true;
			MapOn[5] = true;
		}
	}

	// ##### 4 <-- 5  #####
	if (CurrMapNum == 5) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[4])) {
			//MovingCamera[5] = true;
			MovingCamera[4] = true;
			MapOn[4] = true;
		}
	}


	// ##### 5 --> 6  #####
	if (CurrMapNum == 5) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[5])) {
			//MovingCamera[6] = true;
			MovingCamera[5] = true;
			MapOn[6] = true;
		}
	}

	
	// ##### 6 --> 7  #####
	if (CurrMapNum == 6) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[6])) {
			//MovingCamera[7] = true;
			MovingCamera[6] = true;
			MapOn[7] = true;
		}
	}

	// ##### 7 --> 8  #####
	if (CurrMapNum == 7) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[7])) {
			//MovingCamera[8] = true;
			MovingCamera[7] = true;
			MapOn[8] = true;
		}
	}

	//// ##### 7 <-- 8  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[7])) {
			//MovingCamera[8] = true;
			MovingCamera[7] = true;
			MapOn[7] = true;
		}
	}

	// ##### 8 --> 9  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[8])) {
			//MovingCamera[9] = true;
			MovingCamera[8] = true;
			MapOn[9] = true;
		}
	}

	//// ##### 9 <-- 8  #####
	if (CurrMapNum == 9) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[8])) {
			//MovingCamera[9] = true;
			MovingCamera[8] = true;
			MapOn[8] = true;
		}
	}


	// ##### 8 --> 10  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[9])) {
			MovingCamera[9] = true;
			//MovingCamera[8] = true;
			MapOn[10] = true;
		}
	}

	// ##### 12 --> 13  #####
	if (CurrMapNum == 12) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[12])) {
			MovingCamera[12] = true;
			MapOn[13] = true;
		}
	}


	// ##### 13 --> 14  #####
	if (CurrMapNum == 13) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[13])) {
			MovingCamera[13] = true;
			MapOn[14] = true;
		}
	}

	//// ##### 13 <-- 14  #####
	if (CurrMapNum == 14) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[13])) {
			MovingCamera[13] = true;
			MapOn[13] = true;
		}
	}


	// ##### 13 --> 15 #####
	if (CurrMapNum == 13) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[14])) {
			MovingCamera[14] = true;
			MapOn[15] = true;
		}
	}


	// ##### 15 --> 16 #####
	if (CurrMapNum == 15) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[15])) {
			MovingCamera[15] = true;
			MapOn[16] = true;
		}
	}

	//// ##### 15 <-- 16  #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[15])) {
			MovingCamera[15] = true;
			MapOn[15] = true;
		}
	}

	// ##### 15 --> 16 #####
	if (CurrMapNum == 15) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[16])) {
			MovingCamera[15] = true;
			MapOn[16] = true;
		}
	}

	//// ##### 15 <-- 16  #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[16])) {
			MovingCamera[15] = true;
			MapOn[15] = true;
		}
	}


	// ##### 16 --> 17 #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[17])) {
			MovingCamera[16] = true;
			MapOn[17] = true;
		}
	}

	
	// ##### 17 --> 18 #####
	if (CurrMapNum == 17) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[18])) {
			MovingCamera[17] = true;
			MapOn[18] = true;
		}
	}


	// ##### 18 --> 19 #####
	if (CurrMapNum == 18) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[19])) {
			MovingCamera[18] = true;
			MapOn[19] = true;
		}
	}

	// ##### 19 --> 20 #####
	if (CurrMapNum == 19) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[20])) {
			MovingCamera[19] = true;
			MapOn[20] = true;
		}
	}

	// ##### 20 --> 21 #####
	if (CurrMapNum == 20) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[21])) {
			MovingCamera[20] = true;
			MapOn[21] = true;
		}
	}

	// ##### 21 --> 23 #####
	if (CurrMapNum == 21) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[22])) {
			MovingCamera[21] = true;
			MapOn[22] = true;
		}
	}

	// ##### 23 --> 24 #####
	if (CurrMapNum == 22) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &CheckChangeMapRect[23])) {
			MovingCamera[22] = true;
			MapOn[23] = true;
		}
	}
}

void MapManager::MovingMap()
{
	// ##### 0 --> 1  #####
	if (MovingCamera[0] == true && CurrMapNum == 0) {
		if (m_Camera.x < 1600) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (1605 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 1600) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 1600;
				CurrMapNum = 1;
				MovingCamera[0] = false;
				MapOn[0] = false;
				m_pEnemyMgr->setBug();
				m_pObjectMgr->setDirtblock();
				PushRect();
			}
		}
	}

	// ##### 0 <-- 1  #####
	if (CurrMapNum == 1 && MovingCamera[0] == true) {
		if (m_Camera.x > 1203) {
			m_Camera.x -= 6;
			if (1565 < PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 1203) {
				CurrMapNum = 0;
				MovingCamera[0] = false;
				MapOn[1] = false;
				//PushRect();
			}
		}
	}


	// ##### 1 --> 2  #####
	if (MovingCamera[1] == true && CurrMapNum == 1) {
		if (m_Camera.x < 2000) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (2004 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2000) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2000;
				//PLAYER->SetCurr(2);
				CurrMapNum = 2;
				MovingCamera[1] = false;
				MapOn[1] = false;
				m_pObjectMgr->setBubleBuble();
				PushRect();
			}
		}
	}

	// ##### 1 <-- 2  #####
	if (CurrMapNum == 2 && MovingCamera[1] == true) {
		if (m_Camera.x > 1600) {
			m_Camera.x -= 6;
			PLAYER->setIsMovingMap(true);
			if (1973 < PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 1600) {
				PLAYER->setIsMovingMap(false);
				CurrMapNum = 1;
				MovingCamera[1] = false;
				MapOn[2] = false;
				m_pEnemyMgr->setBug();
				m_pObjectMgr->setDirtblock();
				PushRect();
			}
		}
	}


	// ##### 2 --> 3  #####
	if (MovingCamera[2] == true && CurrMapNum == 2) {
		if (m_Camera.y > 426) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (620 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.4f);
				PLAYER->setState(P_LADDERUP);
			}
			if (m_Camera.y <= 426) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 424;
				CurrMapNum = 3;
				MovingCamera[2] = false;
				m_pEnemyMgr->setBug();
				m_pObjectMgr->setMovingFloor();
				PushRect();
			}
		}
	}

	// ##### 3 --> 4  #####
	if (MovingCamera[3] == true && CurrMapNum == 3 && PLAYER->getIsAfterLoad() == false) {
		if (m_Camera.x < 2400) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (2410 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2400;
				CurrMapNum = 4;
				MovingCamera[3] = false;
				MapOn[3] = false;
				m_pObjectMgr->setDirtblock();
				m_pObjectMgr->setSmallBlock();
				m_pObjectMgr->setMovingFloor();
				PushRect();
			}
		}
	}

	// ##### 3 --> 4  ##### ¼¼ÀÌºê ÈÄ
	if (MovingCamera[3] == true && CurrMapNum == 3 && PLAYER->getIsAfterLoad() == true) {
		if (m_Camera.x < 2400) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (2410 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2400;
				CurrMapNum = 4;
				MovingCamera[3] = false;
				MapOn[3] = false;
				m_pObjectMgr->setDirtblock();
				m_pObjectMgr->setSmallBlock();
			}
		}
	}

	// ##### 3 <-- 4  #####
	if (MovingCamera[3] == true && CurrMapNum == 4) {
		if (m_Camera.x > 2000) {
			m_Camera.x -= 6;
			PLAYER->setIsMovingMap(true);
			if (2350 < PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 2000) {
				PLAYER->setIsMovingMap(false);
				MapOn[4] = false;
				CurrMapNum = 3;
				MovingCamera[3] = false;
				m_pEnemyMgr->setBug();
				//PushRect();
			}
		}
	}


	// ##### 4 --> 5  #####
	if (MovingCamera[4] == true && CurrMapNum == 4) {
		if (m_Camera.x < 2800) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (2810 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2800) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2800;
				CurrMapNum = 5;
				MovingCamera[4] = false;
				m_pEnemyMgr->setBubleDragon();
				PushRect();
			}
		}
	}


	// ##### 5 --> 6  #####
	if (MovingCamera[5] == true && CurrMapNum == 5) {
		if (m_Camera.y < 634) {
			m_Camera.y += 5;
			PLAYER->setIsMovingMap(true);
			if (670 > PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() + 0.5f);
			}
			if (m_Camera.y >= 634) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 634;
				CurrMapNum = 6;
				MovingCamera[5] = false;
				MapOn[5] = false;
				m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}

	// ##### 6 --> 7  #####
	if (MovingCamera[6] == true && CurrMapNum == 6) {
		if (m_Camera.y < 842) {
			m_Camera.y += 5;
			PLAYER->setIsMovingMap(true);
			if (863 > PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() + 0.5f);
			}
			if (m_Camera.y >= 842) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 842;
				CurrMapNum = 7;
				MovingCamera[6] = false;
				MapOn[6] = false;
				m_pObjectMgr->setDirtblock();
				PushRect();
			}
		}
	}

	// ##### 7 --> 8  #####
	if (MovingCamera[7] == true && CurrMapNum == 7) {
		if (m_Camera.y < 1050) {
			m_Camera.y += 5;
			PLAYER->setIsMovingMap(true);
			if (1070 > PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() + 0.5f);
			}
			if (m_Camera.y >= 1050) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 1050;
				CurrMapNum = 8;
				MovingCamera[7] = false;
				MapOn[7] = false;
				//m_pObjectMgr->setDirtblock();
				PushRect();
			}
		}
	}

	
	// ##### 8 --> 9  #####
	if (MovingCamera[8] == true && CurrMapNum == 8) {
		if (m_Camera.x > 2400) {
			m_Camera.x -= 6;
			PLAYER->setIsMovingMap(true);
			if (2760 < PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 2400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2400;
				CurrMapNum = 9;
				MovingCamera[8] = false;
				MapOn[8] = false;
				PushRect();
			}
		}
	}

	// ##### 8 <-- 9  #####
	if (MovingCamera[8] == true && CurrMapNum == 9) {
		if (m_Camera.x < 2800) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (2810 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2800) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 2800;
				CurrMapNum = 8;
				MovingCamera[8] = false;
				MapOn[9] = false;
				//PushRect();
			}
		}
	}


	// ##### 8 --> 10  #####
	if (MovingCamera[9] == true && CurrMapNum == 8) {
		if (m_Camera.x < 3200) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (3240 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 3200) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 3200;
				CurrMapNum = 12;
				MovingCamera[9] = false;
				MapOn[8] = false;
				m_pEnemyMgr->setSmallDragon();
				m_pObjectMgr->setDirtblock();
				m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}

	
	// ##### 12 --> 13  #####
	if (MovingCamera[12] == true && CurrMapNum == 12) {
		if (m_Camera.y > 842) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (995 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.5f);
			}
			if (m_Camera.y <= 842) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 842;
				m_Camera.x = 4000;
				CurrMapNum = 13;
				MovingCamera[12] = false;
				MapOn[10] = false;
				m_pObjectMgr->setMovingFloor();
				m_pEnemyMgr->setSmallDragon();
				PushRect();
			}
		}
	}


	// ##### 13 --> 14  #####
	if (MovingCamera[13] == true && CurrMapNum == 13) {
		if (m_Camera.x < 4400) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (4600 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 4400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 4400;
				CurrMapNum = 14;
				MovingCamera[13] = false;
				MapOn[13] = false;
				
				//m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}

	// ##### 13 <-- 14  #####
	if (MovingCamera[13] == true && CurrMapNum == 14) {
		if (m_Camera.x > 4000) {
			m_Camera.x -= 6;
			PLAYER->setIsMovingMap(true);
			if (4365 < PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 4000) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 4000;
				CurrMapNum = 13;
				MovingCamera[13] = false;
				MapOn[14] = false;
			}
		}
	}


	// ##### 13 --> 15  #####
	if (MovingCamera[14] == true && CurrMapNum == 13) {
		if (m_Camera.y > 634) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (785 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.5f);
			}
			if (m_Camera.y <= 634) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 634;
				CurrMapNum = 15;
				MovingCamera[14] = false;
				MapOn[13] = false;
				m_pEnemyMgr->setSmallDragon();
				//m_pObjectMgr->setDirtblock();
				//m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}


	// ##### 15 --> 16  #####
	if (MovingCamera[15] == true && CurrMapNum == 15) {
		if (m_Camera.y > 426) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (600 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 426) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 426;
				CurrMapNum = 16;
				MovingCamera[15] = false;
				MapOn[15] = false;
				//m_pObjectMgr->setDirtblock();
				//m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}

	// ##### 15 <-- 16  #####
	if (MovingCamera[15] == true && CurrMapNum == 16) {
		if (m_Camera.y < 634) {
			m_Camera.y += 5;
			PLAYER->setIsMovingMap(true);
			if (640 > PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() + 0.5f);
			}
			if (m_Camera.y >= 634) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 634;
				CurrMapNum = 15;
				MovingCamera[15] = false;
				MapOn[16] = false;
			}
		}
	}


	// ##### 16 --> 17  #####
	if (MovingCamera[16] == true && CurrMapNum == 16) {
		if (m_Camera.x < 4400) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (4600 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 4400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 4400;
				CurrMapNum = 17;
				MovingCamera[16] = false;
				MapOn[16] = false;
				m_pObjectMgr->setMovingFloor();
				PushRect();
			}
		}
	}


	// ##### 17 --> 18  #####
	if (MovingCamera[17] == true && CurrMapNum == 17) {
		if (m_Camera.x < 5200) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (5250 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 5200) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 5200;
				CurrMapNum = 18;
				MovingCamera[17] = false;
				MapOn[17] = false;
				m_pEnemyMgr->setBubleDragon();
				PushRect();
			}
		}
	}

	// ##### 18 --> 19  #####
	if (MovingCamera[18] == true && CurrMapNum == 18) {
		if (m_Camera.x < 5600) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (5650 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 5600) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 5600;
				CurrMapNum = 19;
				MovingCamera[18] = false;
				MapOn[18] = false;
				PushRect();
			}
		}
	}

	// ##### 19 --> 20  #####
	if (MovingCamera[19] == true && CurrMapNum == 19) {
		if (m_Camera.y > 218) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (150 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.5f);
			}
			if (m_Camera.y <= 218) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 218;
				CurrMapNum = 20;
				MovingCamera[19] = false;
				MapOn[19] = false;
				m_pObjectMgr->setSmallBlock();
				PushRect();
			}
		}
	}


	// ##### 20 --> 21  #####
	if (MovingCamera[20] == true && CurrMapNum == 20) {
		if (m_Camera.y > 10) {
			m_Camera.y -= 5;
			PLAYER->setIsMovingMap(true);
			if (0 < PLAYER->getPlayerY()) {
				PLAYER->SetPlayerY(PLAYER->getPlayerY() - 0.5f);
			}
			if (m_Camera.y <= 10) {
				PLAYER->setIsMovingMap(false);
				m_Camera.y = 10;
				CurrMapNum = 21;
				MovingCamera[20] = false;
				MapOn[20] = false;
				m_pEnemyMgr->setSmallDragon();
				PushRect();
			}
		}
	}


	// ##### 21 --> 22  #####
	if (MovingCamera[21] == true && CurrMapNum == 21) {
		if (m_Camera.x < 6000) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (6050 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 6000) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 6000;
				CurrMapNum = 22;
				MovingCamera[21] = false;
				MapOn[21] = false;
				PushRect();
			}
		}
	}

	// ##### 22 --> 23  #####
	if (MovingCamera[22] == true && CurrMapNum == 22) {
		if (m_Camera.x < 6400) {
			m_Camera.x += 6;
			PLAYER->setIsMovingMap(true);
			if (6450 > PLAYER->getPlayerX()) {
				PLAYER->SetPlayerX(PLAYER->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 6400) {
				PLAYER->setIsMovingMap(false);
				m_Camera.x = 6400;
				CurrMapNum = 23;
				MovingCamera[22] = false;
				MapOn[22] = false;
				PushRect();
			}
		}
	}
}

void MapManager::PushRect()
{
	if (CurrMapNum == 100) {
		_RectInfo._rc = RectMake(0, 207, 450, 15);
		vRect.push_back(_RectInfo);
	}
	// 0¹ø¸Ê
	if (CurrMapNum == 0) {
		_RectInfo._rc = RectMake(-30, 823, 1470, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(608, 790, 65, 35);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(673, 759, 47, 66);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(720, 790, 65, 35);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(830, 759, 130, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1009, 759, 47, 66);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1120, 743, 80, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1230, 807, 50, 17);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1280, 790, 65, 40);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1345, 807, 94, 17);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1472, 790, 280, 60);
		vRect.push_back(_RectInfo);
	}


	// 1¹ø¸Ê
	if (CurrMapNum == 1) {

		// 0¹ø¸ÊÀ» ´Ù »èÁ¦
		vRect.erase(vRect.begin(), vRect.begin() + 11); 

		_RectInfo._rc = RectMake(1472, 790, 280, 60);
		vRect.push_back(_RectInfo);
	
		_RectInfo._rc = RectMake(1729, 759, 35, 80);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1760, 727, 31, 80);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1791, 823, 163, 30);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1823, 674, 30, 100);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(1951, 791, 177, 52);
		vRect.push_back(_RectInfo);
	}

	// 2¹ø¸Ê
	if (CurrMapNum == 2) {

		_RectInfo._rc = RectMake(1951, 791, 177, 52);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2126, 822, 100, 52);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2225, 742, 80, 122);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2306, 615, 20, 132);
		vRect.push_back(_RectInfo);
		// »ç´Ù¸®
		_RectLadder._rc = RectMake(2294, 613, 6, 132);
		vLadderRect.push_back(_RectLadder);
	}


	// 3¹ø¸Ê
	if (CurrMapNum == 3) {

		_RectInfo._rc = RectMake(2019, 615, 270, 40);
		vRect.push_back(_RectInfo);

		_RectSave._rc = RectMake(2164, 567, 1, 50);
		vSaveRect.push_back(_RectSave);

		_RectLadder._rc = RectMake(2037, 465, 6, 132);
		vLadderRect.push_back(_RectLadder);

		_RectInfo._rc = RectMake(2050, 518, 29, 20);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2305, 519, 143, 60);
		vRect.push_back(_RectInfo);
	}


	// 4¹ø¸Ê 
	if (CurrMapNum == 4) {

		_RectInfo._rc = RectMake(2305, 518, 143, 60);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2432, 615, 80, 40);
		vRect.push_back(_RectInfo);

		_RectSpike._rc = RectMake(2515, 630, 160, 40);
		vSpikeRect.push_back(_RectSpike);

		_RectInfo._rc = RectMake(2688, 615, 430, 40);
		vRect.push_back(_RectInfo);
	}


	// 5¹ø¸Ê
	if (CurrMapNum == 5) {

		vRect.erase(vRect.begin(), vRect.begin() + 16);

		_RectInfo._rc = RectMake(2688, 615, 430, 40);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(3140, 615, 6, 30);
		vLadderRect.push_back(_RectLadder);
	}


	// 6¹ø¸Ê
	if (CurrMapNum == 6) {

		_RectInfo._rc = RectMake(2868, 791, 300, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2830, 839, 45, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(2884, 839, 6, 40);
		vLadderRect.push_back(_RectLadder);
	}


	// 7¹ø¸Ê
	if (CurrMapNum == 7) {

		vRect.erase(vRect.begin(), vRect.begin() + 3);

		_RectInfo._rc = RectMake(2814, 1047, 300, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(3093, 981, 6, 60);
		vLadderRect.push_back(_RectLadder);

		_RectInfo._rc = RectMake(2958, 983, 130, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(2965, 917, 6, 60);
		vLadderRect.push_back(_RectLadder);

		_RectInfo._rc = RectMake(2975, 919, 160, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3105, 949, 30, 100);
		vRect.push_back(_RectInfo);

		// ÃµÀå
		_RectInfo._rc = RectMake(2975, 856, 200, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3089, 1110, 80, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2673, 1239, 320, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3049, 1239, 100, 15);
		vRect.push_back(_RectInfo);
	}


	// 8¹ø¸Ê
	if (CurrMapNum == 8) {

		vRect.erase(vRect.begin(), vRect.begin() + 8);

		_RectInfo._rc = RectMake(3089, 1110, 80, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2673, 1239, 320, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3049, 1239, 100, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3157, 1207, 120, 15);
		vRect.push_back(_RectInfo);
	}


	// 9¹ø¸Ê
	if (CurrMapNum == 9) {

		_RectInfo._rc = RectMake(2523, 1239, 100, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(2403, 1239, 100, 15);
		vRect.push_back(_RectInfo);
	}


	// 10¹ø¸Ê
	if (CurrMapNum == 12) {

		vRect.erase(vRect.begin(), vRect.begin() + 6);

		_RectInfo._rc = RectMake(3157, 1207, 120, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3280, 1175, 30, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3320, 1143, 40, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(3350, 1239, 800, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4225, 1239, 65, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4290, 1207, 85, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(4357, 1045, 6, 115);
		vLadderRect.push_back(_RectLadder);
	}


	// 13¹ø ¸Ê
	if (CurrMapNum == 13) {

		vRect.erase(vRect.begin(), vRect.begin() + 6);

		_RectInfo._rc = RectMake(4000, 1046, 350, 15);
		vRect.push_back(_RectInfo);

		/*_RectInfo._rc = RectMake(4080, 976, 80, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4230, 966, 50, 15);
		vRect.push_back(_RectInfo);*/

		_RectInfo._rc = RectMake(4335, 967, 100, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(4004, 805, 6, 130);
		vLadderRect.push_back(_RectLadder);
	}


	// 14¹ø ¸Ê 
	if (CurrMapNum == 14) {
		_RectInfo._rc = RectMake(4420, 998, 60, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4520, 998, 60, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4609, 998, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4749, 998, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4879, 998, 90, 15);
		vRect.push_back(_RectInfo);
	}

	// 15¹ø ¸Ê
	if (CurrMapNum == 15) {

		vRect.erase(vRect.begin(), vRect.begin() + 7);

		_RectInfo._rc = RectMake(4023, 807, 290, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4133, 743, 220, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(4101, 614, 6, 80);
		vLadderRect.push_back(_RectLadder);

		_RectLadder._rc = RectMake(4277, 629, 6, 50);
		vLadderRect.push_back(_RectLadder);
	}

	// 16¹ø ¸Ê
	if (CurrMapNum == 16) {

		vRect.erase(vRect.begin(), vRect.begin() + 2);

		_RectInfo._rc = RectMake(4112, 616, 40, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4283, 631, 70, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4159, 583, 40, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4210, 551, 280, 15);
		vRect.push_back(_RectInfo);
	}

	// 17¹ø ¸Ê
	if (CurrMapNum == 17) {

		vRect.erase(vRect.begin(), vRect.begin() + 4);

		_RectInfo._rc = RectMake(4210, 550, 280, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4529, 600, 80, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4609, 583, 130, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4739, 567, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(4875, 600, 65, 15);
		vRect.push_back(_RectInfo);

		/*_RectInfo._rc = RectMake(4945, 570, 65, 15);
		vRect.push_back(_RectInfo);*/

		_RectInfo._rc = RectMake(5065, 519, 180, 15);
		vRect.push_back(_RectInfo);
	}

	// 18¹ø ¸Ê
	if (CurrMapNum == 18) {

		vRect.erase(vRect.begin(), vRect.begin() + 6);

		_RectInfo._rc = RectMake(5065, 519, 180, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5280, 631, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5433, 631, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5553, 599, 140, 15);
		vRect.push_back(_RectInfo);
	}

	// 19¹ø ¸Ê
	if (CurrMapNum == 19) {

		vRect.erase(vRect.begin(), vRect.begin() + 4);

		_RectInfo._rc = RectMake(5553, 599, 140, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5748, 599, 110, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5908, 599, 20, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(5974, 290, 6, 300);
		vLadderRect.push_back(_RectLadder);
	}

	// 20¹ø ¸Ê
	if (CurrMapNum == 20) {

		vRect.erase(vRect.begin(), vRect.begin() + 3);

		_RectInfo._rc = RectMake(5919, 294, 40, 120);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5808, 235, 200, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5608, 424, 350, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5590, 359, 100, 15);
		vRect.push_back(_RectInfo);

		_RectLadder._rc = RectMake(5733, 117, 6, 160);
		vLadderRect.push_back(_RectLadder);
	}

	// 21¹ø ¸Ê
	if (CurrMapNum == 21) {

		vRect.erase(vRect.begin(), vRect.begin() + 4);
		//vLadderRect.erase(vLadderRect.begin(), vLadderRect.begin() + 12);

		_RectInfo._rc = RectMake(5750, 118, 50, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5815, 150, 50, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5875, 182, 50, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(5940, 200, 220, 15);
		vRect.push_back(_RectInfo);

	}


	// 22¹ø ¸Ê
	if (CurrMapNum == 22) {

		vRect.erase(vRect.begin(), vRect.begin() + 4);
		//vLadderRect.erase(vLadderRect.begin(), vLadderRect.begin() + 12);

		_RectInfo._rc = RectMake(5940, 200, 220, 15);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(6165, 135, 80, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(6253, 167, 40, 50);
		vRect.push_back(_RectInfo);

		_RectInfo._rc = RectMake(6253, 199, 600, 15);
		vRect.push_back(_RectInfo);
	}

	// 23¹ø ¸Ê
	if (CurrMapNum == 23) {

		vRect.erase(vRect.begin(), vRect.begin() + 4);
		vLadderRect.erase(vLadderRect.begin(), vLadderRect.begin() + 12);

		_RectInfo._rc = RectMake(6300, 199, 505, 15);
		vRect.push_back(_RectInfo);
	}
}

void MapManager::CollisionMap()
{
	for (int i = 0; i < vRect.size(); i++) {
		if (PLAYER->getHP() >= 0) {
			PLAYER->RectColliosion(MAPMANAGER->getMapVectorRc(i));
		}
	}

	for (int i = 0; i < vLadderRect.size(); i++) {
		PLAYER->LadderColliosion(MAPMANAGER->getLadderVECRc(i));
	}

	for (int i = 0; i < vSpikeRect.size(); i++) {
		PLAYER->SpikeColliosion(MAPMANAGER->getSpikeVECRc(i));
	}

	for (int i = 0; i < vSaveRect.size(); i++) {
		PLAYER->SaveColliosion(MAPMANAGER->getSaveVECRc(i));
	}
}

void MapManager::CollisionEnemy()
{
	vector<bug*> vBug = m_pEnemyMgr->getVecBug();
	vector<bug*>::iterator iter;

	for (iter = vBug.begin(); iter != vBug.end();) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iter)->getRect())) {
			(*iter)->damage(1);
			iter = vBug.erase(iter);
		}

		else if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iter)->getRect())) {
			(*iter)->damage(1);
			PLAYER->DownATKCollision((*iter)->getRect());
			iter = vBug.erase(iter);
		}

		else iter++;
	}

	for (iter = vBug.begin(); iter != vBug.end(); iter++) {
		RECT rc;
		if (PLAYER->getInvincibleTime() == false) {
			if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &(*iter)->getRect())) {
				PLAYER->setIsDamaged(true);
				PLAYER->setInvincibleTime(true);
			}
		}
	}



	vector<small_Dragon*> vSmallDRG = m_pEnemyMgr->getVecSmallDRG();
	vector<small_Dragon*>::iterator iterSMALL;

	for (iterSMALL = vSmallDRG.begin(); iterSMALL != vSmallDRG.end();) {
		RECT rc;
		if ((*iterSMALL)->getIsAlive() == true && IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iterSMALL)->getRect())) {
			(*iterSMALL)->setCrash(true);

			if ((*iterSMALL)->getCrash() == true) (*iterSMALL)->damage(1);
			
			if ((*iterSMALL)->getHP() <= 0) {
				iterSMALL = vSmallDRG.erase(iterSMALL);
			}
		}

		/*else if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterSMALL)->getRect())) {
			(*iterSMALL)->damage(1);
			PLAYER->DownATKCollision((*iterSMALL)->getRect());
			iterSMALL = vSmallDRG.erase(iterSMALL);
		}
*/
		else iterSMALL++;
	}

	for (iterSMALL = vSmallDRG.begin(); iterSMALL != vSmallDRG.end(); iterSMALL++) {
		RECT rc;
		if (PLAYER->getInvincibleTime() == false) {
			if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &(*iterSMALL)->getRect())) {
				PLAYER->setIsDamaged(true);
				PLAYER->setInvincibleTime(true);
			}
		}
	}
}

void MapManager::CollisionBoss()
{
	vector<bubble_Dragon*> vBBD = m_pEnemyMgr->getVecBBD();
	vector<bubble_Dragon*>::iterator iterBBD;

	for (iterBBD = vBBD.begin(); iterBBD != vBBD.end();) {
		RECT rc;
		if ((*iterBBD)->getLife() > 0) {
			if (IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iterBBD)->getHead())) {
				(*iterBBD)->damage(1);
			}

			else if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterBBD)->getHead())) {
				(*iterBBD)->damage(1);
				PLAYER->DownATKCollision((*iterBBD)->getHead());
			}

			if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterBBD)->getBody())) {
				PLAYER->DownATKtoOBJCollision((*iterBBD)->getBody());
			}
		}

		if ((*iterBBD)->getLife() == 0) {
			iterBBD = vBBD.erase(iterBBD);
		}
		else iterBBD++;
	}

	for (iterBBD = vBBD.begin(); iterBBD != vBBD.end(); iterBBD++) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterBBD)->getBody())) {
			PLAYER->DownATKtoOBJCollision((*iterBBD)->getBody());
		} 
	}



	for (iterBBD = vBBD.begin(); iterBBD != vBBD.end(); iterBBD++) {

		vector<bubble*> vbuble = (*iterBBD)->getOBJMgr()->getVecBubble();
		vector<bubble*>::iterator iterBuble;

		for (iterBuble = vbuble.begin(); iterBuble != vbuble.end();) {
			RECT rc;
			if ((*iterBuble)->getIsFire() == true && IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterBuble)->getRECT())) {
				PLAYER->DownATKtoOBJCollision((*iterBuble)->getRECT());
				((*iterBuble)->setIsFire(false));
				iterBuble = vbuble.erase(iterBuble);
			}

			else if ((*iterBuble)->getIsFire() == true && IntersectRect(&rc, &PLAYER->getPlayerRect(), &(*iterBuble)->getRECT())) {
				if (PLAYER->getInvincibleTime() == false) {
					PLAYER->setIsDamaged(true);
					PLAYER->setInvincibleTime(true);
					
				}
				((*iterBuble)->setIsFire(false));
				iterBuble = vbuble.erase(iterBuble);
			}

			else iterBuble++;
		}
	}
}

void MapManager::CollisionObject()
{
	vector<PileOfRocks*> vPOR = m_pObjectMgr->getVecPOR();
	vector<PileOfRocks*>::iterator iter;

	for (iter = vPOR.begin(); iter != vPOR.end();) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iter)->getRect())) {
			(*iter)->DigOut();
			iter = vPOR.erase(iter);
		}

		else iter++;
	}

	vector<dirtBlock*> vdirt = m_pObjectMgr->getVecDIRT();
	vector<dirtBlock*>::iterator iterDIrt;

	for (iterDIrt = vdirt.begin(); iterDIrt != vdirt.end();) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iterDIrt)->getRect())) {
			(*iterDIrt)->DigOut();
			(*iterDIrt)->setCrash(true);
			iterDIrt = vdirt.erase(iterDIrt);
		}

		else if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterDIrt)->getRect())) {
			PLAYER->DownATKtoOBJCollision((*iterDIrt)->getRect());
			(*iterDIrt)->DigOut();
			(*iterDIrt)->setCrash(true);
			iterDIrt = vdirt.erase(iterDIrt);
		}

		else iterDIrt++;
	}

	for (iterDIrt = vdirt.begin(); iterDIrt != vdirt.end(); iterDIrt++) {
		PLAYER->OBJCollision((*iterDIrt)->getRect());
	}



	vector<dirtBlock_Small*> vSmall = m_pObjectMgr->getVecSmall();
	vector<dirtBlock_Small*>::iterator iterSmall;

	for (iterSmall = vSmall.begin(); iterSmall != vSmall.end();) {
		RECT rc;
		if (IntersectRect(&rc, &PLAYER->getAttacRect(), &(*iterSmall)->getRect())) {
			(*iterSmall)->DigOut();
			(*iterSmall)->setCrash(true);
			iterSmall = vSmall.erase(iterSmall);
		}

		else if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterSmall)->getRect())) {
			PLAYER->DownATKtoOBJCollision((*iterSmall)->getRect());
			(*iterSmall)->DigOut();
			(*iterSmall)->setCrash(true);
			iterSmall = vSmall.erase(iterSmall);
		}

		else iterSmall++;
	}

	for (iterSmall = vSmall.begin(); iterSmall != vSmall.end(); iterSmall++) {
		PLAYER->OBJCollision((*iterSmall)->getRect());
	}



	vector<movingFloor*> vMoving = m_pObjectMgr->getVecMoving();
	vector<movingFloor*>::iterator iterMoving;

	for (iterMoving = vMoving.begin(); iterMoving != vMoving.end(); iterMoving++) {
		RECT rc;
		if (PLAYER->getHP() > 0) {
			if (IntersectRect(&rc, &PLAYER->getPlayerRect(), &(*iterMoving)->getRect())) {

				if ((*iterMoving)->getIsRight() == true && (*iterMoving)->getMoveRight() == true &&
					(*iterMoving)->getIsUp() == false && (*iterMoving)->getMoveUp() == false) {
					PLAYER->SetPlayerX(PLAYER->getPlayerX() + 1.5f);
				}
				else if ((*iterMoving)->getIsRight() == false && (*iterMoving)->getMoveRight() == true &&
					(*iterMoving)->getIsUp() == false && (*iterMoving)->getMoveUp() == false) {
					PLAYER->SetPlayerX(PLAYER->getPlayerX() - 1.5f);
				}

				if ((*iterMoving)->getIsUp() == true && (*iterMoving)->getMoveUp() == true &&
					(*iterMoving)->getIsRight() == false && (*iterMoving)->getMoveRight() == false) {
					PLAYER->SetPlayerY(PLAYER->getPlayerY() - 1.0f);
				}
				else if ((*iterMoving)->getIsUp() == false && (*iterMoving)->getMoveUp() == true &&
					(*iterMoving)->getIsRight() == false && (*iterMoving)->getMoveRight() == false) {
					PLAYER->SetPlayerY(PLAYER->getPlayerY() + 6.0f);
				}
			}
		}
		

		if (PLAYER->getHP() > 0) {
			PLAYER->OBJCollision((*iterMoving)->getRect());
		}
	}


	vector<BubleBuble*> vBBB = m_pObjectMgr->getVecBB();
	vector<BubleBuble*>::iterator iterBBB;

	for (iterBBB = vBBB.begin(); iterBBB != vBBB.end();) {
		RECT rc;

		if (IntersectRect(&rc, &PLAYER->getAttacDWRect(), &(*iterBBB)->getRect())) {
			PLAYER->DownATKtoOBJCollision((*iterBBB)->getRect());
			(*iterBBB)->setIsAlive(false);
			iterBBB = vBBB.erase(iterBBB);
		}

		else iterBBB++;
	}
}

void MapManager::ScreenEffect()
{
	if (ScreenSFXOn == true) {
		m_FrameCount++;
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_Screen->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX >= 8) {
				m_CurrFrameX = 8;
			}
		}
	}

	if (ScreenSFXREV && PLAYER->getPlayerY() >= 789) {
		m_FrameCount++;
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX--;
			m_Screen->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX <= 0) {
				m_CurrFrameX = 0;
				ScreenSFXREV = false;
				PLAYER->setAppear(true);
			}
		}
	}

	if (ScreenSFXREV2 && PLAYER->getHP() <= 0) {
		ScreenSFXOn = false;
		m_FrameCount++;

		if (m_FrameCount % 7 == 0) {
			m_screenFrame--;
			m_Screen->setFrameX(m_screenFrame);

			if (m_screenFrame <= 0) {
				m_screenFrame = 0;
				PLAYER->setHp(12);
				ScreenSFXREV2 = false;
			}
		}
	}

	if (SaveCheck) {
		m_FrameCount++;
		if (m_FrameCount % 7 == 0) {
			m_CheckSaveFrame++;
			m_SaveCheckPoint->setFrameX(m_CheckSaveFrame);

			if (m_CheckSaveFrame >= 11) {
				m_CheckSaveFrame = 8;
			}
		}
	}
}

void MapManager::SavePoint()
{
	sprintf_s(m_szText, "%f", PLAYER->getPlayerX());
	sprintf_s(m_szText2, "%f", PLAYER->getPlayerY());
	sprintf_s(m_szText3, "%d", m_Camera.x);
	sprintf_s(m_szText4, "%d", m_Camera.y);
	sprintf_s(m_szText5, "%d", PLAYER->getHP());

	vec.push_back(m_szText);
	vec.push_back(m_szText2);
	vec.push_back(m_szText3);
	vec.push_back(m_szText4);
	vec.push_back(m_szText5);
	TXTDATA->txtSave("test.txt", vec);
}

void MapManager::LoadPoint()
{
	MapOn[4] = false;
	MapOn[3] = true;
	m_pEnemyMgr->setBug();
	CurrMapNum = 3;
	PLAYER->setIsAfterLoad(true);
	PLAYER->SetPlayerX(atof(m_szText));
	PLAYER->SetPlayerY(atof(m_szText2));
	MAPMANAGER->setCameraX(atoi(m_szText3));
	MAPMANAGER->setCameraY(atoi(m_szText4));
	PLAYER->setHp(atoi(m_szText5));
	m_vecLoad = TXTDATA->txtLoad("test.txt");
}

MapManager::MapManager() :m_Camera({ 0 , 0 }),  _empty(new image)
{
}


MapManager::~MapManager()
{
}
