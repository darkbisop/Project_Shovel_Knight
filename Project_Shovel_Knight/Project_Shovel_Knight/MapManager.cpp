#include "stdafx.h"
#include "MapManager.h"
#include "Player.h"
#include "MapImage.h"

HRESULT MapManager::init(void)
{
	_empty = IMAGEMANAGER->addImage("MainCamera", "image/Empty.bmp", 7200, 1400, true, RGB(255, 0, 255));
	m_UI = IMAGEMANAGER->addImage("UI", "image/UI.bmp", 400, 18, true, RGB(255, 0, 255));
	BackGround_Castle = IMAGEMANAGER->addImage("Background_Castle", "image/BackGround/Background_Castle.bmp", 2500, 176, true, RGB(255, 0, 255));
	Back_3_Ground = IMAGEMANAGER->addImage("Back_3_Ground", "image/BackGround/Back_3_Ground.bmp", 1000, 108, true, RGB(255, 0, 255));
	Back_2_Ground = IMAGEMANAGER->addImage("Back_2_Ground", "image/BackGround/Back_2_Ground.bmp", 1000, 176, true, RGB(255, 0, 255));
	Back_Ground = IMAGEMANAGER->addImage("Back_Ground", "image/BackGround/Back_Ground.bmp", 2500, 199, true, RGB(255, 0, 255));

	m_SkyBg = IMAGEMANAGER->addImage("SkyBG", "image/BackGround/Sky.bmp", 399, 208, true, RGB(255, 0, 255));

	m_pMapImage = new MapImage;
	m_pMapImage->init();

	m_pPlayerLink = new Player;
	m_pPlayerLink->init();

	MapOn[0] = true;
	
	for (int i = 0; i < 24; i++) {
		MovingCamera[i] = false;
	}

	for (int i = 1; i < 24; i++) {
		MapOn[i] = false;
	}

	CurrMapNum = 0;

	CheckMapRect();

	return S_OK;
}

void MapManager::release(void)
{
	SAFE_DELETE(m_pPlayerLink);
}

void MapManager::update(void)
{
	m_pPlayerLink->update();
	CollisionCheck_ChangeMapRect();
	MovingMap();
}

void MapManager::render(HDC hdc)
{
	m_SkyBg->render(_empty->getMemDC(), m_Camera.x , m_Camera.y);
	
	if (CurrMapNum == 0 || CurrMapNum == 1) {
		BackGround_Castle->loopRender(_empty->getMemDC(), &RectMake(0, 634, 2500, 176), -(int)m_Camera.x * 0.8f, 0);
		Back_3_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 714, 2500, 108), -(int)m_Camera.x * 0.8f, 0);
		Back_2_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 648, 2500, 176), -(int)m_Camera.x * 0.5f, 0);
		Back_Ground->loopRender(_empty->getMemDC(), &RectMake(0, 666, 2500, 199), -(int)m_Camera.x * 0.3f, 0);
	}

	Rectangle(_empty->getMemDC(), CheckChangeMapRect[0].left, CheckChangeMapRect[0].top, CheckChangeMapRect[0].right, CheckChangeMapRect[0].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[1].left, CheckChangeMapRect[1].top, CheckChangeMapRect[1].right, CheckChangeMapRect[1].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[2].left, CheckChangeMapRect[2].top, CheckChangeMapRect[2].right, CheckChangeMapRect[2].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[3].left, CheckChangeMapRect[3].top, CheckChangeMapRect[3].right, CheckChangeMapRect[3].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[4].left, CheckChangeMapRect[4].top, CheckChangeMapRect[4].right, CheckChangeMapRect[4].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[5].left, CheckChangeMapRect[5].top, CheckChangeMapRect[5].right, CheckChangeMapRect[5].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[6].left, CheckChangeMapRect[6].top, CheckChangeMapRect[6].right, CheckChangeMapRect[6].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[7].left, CheckChangeMapRect[7].top, CheckChangeMapRect[7].right, CheckChangeMapRect[7].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[8].left, CheckChangeMapRect[8].top, CheckChangeMapRect[8].right, CheckChangeMapRect[8].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[9].left, CheckChangeMapRect[9].top, CheckChangeMapRect[9].right, CheckChangeMapRect[9].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[10].left, CheckChangeMapRect[10].top, CheckChangeMapRect[10].right, CheckChangeMapRect[10].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[11].left, CheckChangeMapRect[11].top, CheckChangeMapRect[11].right, CheckChangeMapRect[11].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[12].left, CheckChangeMapRect[12].top, CheckChangeMapRect[12].right, CheckChangeMapRect[12].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[13].left, CheckChangeMapRect[13].top, CheckChangeMapRect[13].right, CheckChangeMapRect[13].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[14].left, CheckChangeMapRect[14].top, CheckChangeMapRect[14].right, CheckChangeMapRect[14].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[15].left, CheckChangeMapRect[15].top, CheckChangeMapRect[15].right, CheckChangeMapRect[15].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[16].left, CheckChangeMapRect[16].top, CheckChangeMapRect[16].right, CheckChangeMapRect[16].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[17].left, CheckChangeMapRect[17].top, CheckChangeMapRect[17].right, CheckChangeMapRect[17].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[18].left, CheckChangeMapRect[18].top, CheckChangeMapRect[18].right, CheckChangeMapRect[18].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[19].left, CheckChangeMapRect[19].top, CheckChangeMapRect[19].right, CheckChangeMapRect[19].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[20].left, CheckChangeMapRect[20].top, CheckChangeMapRect[20].right, CheckChangeMapRect[20].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[21].left, CheckChangeMapRect[21].top, CheckChangeMapRect[21].right, CheckChangeMapRect[21].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[22].left, CheckChangeMapRect[22].top, CheckChangeMapRect[22].right, CheckChangeMapRect[22].bottom);
	Rectangle(_empty->getMemDC(), CheckChangeMapRect[23].left, CheckChangeMapRect[23].top, CheckChangeMapRect[23].right, CheckChangeMapRect[23].bottom);
	
	CurrMap();
	m_pPlayerLink->render(_empty->getMemDC());

	m_UI->render(_empty->getMemDC(), m_Camera.x, m_Camera.y);
	
	_empty->render(hdc, 0, 0, m_Camera.x, m_Camera.y, WINSIZEX, WINSIZEY);

	char str[64];
	wsprintf(str, "x : %d, y : %d", m_Camera.x, m_Camera.y);
	//sprintf_s(str, "x : %f, y : %f", m_pPlayerLink->getPlayerX(), m_pPlayerLink->getPlayerY());
	TextOut(hdc, 100, 30, str, strlen(str));
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
	CheckChangeMapRect[15] = RectMake(4090, 651, 50, 3);
	CheckChangeMapRect[16] = RectMake(4265, 651, 50, 3);
	CheckChangeMapRect[17] = RectMake(4400, 497, 3, 50);
	CheckChangeMapRect[18] = RectMake(5197, 477, 3, 50);
	CheckChangeMapRect[19] = RectMake(5600, 560, 3, 50);
	CheckChangeMapRect[20] = RectMake(5930, 440, 50, 3);
	CheckChangeMapRect[21] = RectMake(5724, 230, 50, 3);
	CheckChangeMapRect[22] = RectMake(6000, 160, 3, 50);
	CheckChangeMapRect[23] = RectMake(6398, 160, 3, 50);
}

void MapManager::CurrMap()
{
	// 0¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 0 && MovingCamera[0] == false) {

		if (m_pPlayerLink) {
			m_Camera = { (int)m_pPlayerLink->getPlayerX() - 180, (int)m_pPlayerLink->getPlayerY() };
		}
		
		if (m_Camera.x < 2) m_Camera.x = 2;
		else if (m_Camera.x + WINSIZEX > 1600) m_Camera.x = 1600 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 854) m_Camera.y = 854 - WINSIZEY;
	}

	// 10¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 12 && MovingCamera[9] == false && MovingCamera[12] == false) {

		if (m_pPlayerLink) {
			m_Camera = { (int)m_pPlayerLink->getPlayerX() - 180, (int)m_pPlayerLink->getPlayerY() };
		}

		if (m_Camera.x < 3200) m_Camera.x = 3200;
		else if (m_Camera.x + WINSIZEX > 4397) m_Camera.x = 4397 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 1270) m_Camera.y = 1270 - WINSIZEY;
	}

	// 14¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 14 && MovingCamera[13] == false && MovingCamera[14] == false) {

		if (m_pPlayerLink) {
			m_Camera = { (int)m_pPlayerLink->getPlayerX() - 180, (int)m_pPlayerLink->getPlayerY() };
		}
	
		if (m_Camera.x < 4400) m_Camera.x = 4400;
		else if (m_Camera.x + WINSIZEX > 4976) m_Camera.x = 4976 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 1062) m_Camera.y = 1062 - WINSIZEY;
	}

	// 17¹ø¸ÊÀÏ¶§
	if (CurrMapNum == 17 && MovingCamera[16] == false && MovingCamera[17] == false) {

		if (m_pPlayerLink) {
			m_Camera = { (int)m_pPlayerLink->getPlayerX() - 180, (int)m_pPlayerLink->getPlayerY() };
		}

		if (m_Camera.x < 4400) m_Camera.x = 4400;
		else if (m_Camera.x + WINSIZEX > 5200) m_Camera.x = 5200 - WINSIZEX;

		if (m_Camera.y < 0) m_Camera.y = 0;
		else if (m_Camera.y + WINSIZEY > 644) m_Camera.y = 644 - WINSIZEY;
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
	// ##### 0 --> 1  #####
	if (CurrMapNum == 0) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[0])) {
			MovingCamera[0] = true;
			MapOn[1] = true;
		}
	}

	// ##### 0 <-- 1  #####
	if (CurrMapNum == 1) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[0])) {
			MovingCamera[0] = true;
			MapOn[0] = true;
		}
	}

	// ##### 1 --> 2 #####
	if (CurrMapNum == 1) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[1])) {
			//MovingCamera[2] = true;
			MovingCamera[1] = true;
			MapOn[2] = true;
		}
	}

	// ##### 1 <-- 2  #####
	if (CurrMapNum == 2) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[1])) {
			MovingCamera[1] = true;
			MapOn[1] = true;
		}
	}

	// ##### 2 --> 3 #####
	if (CurrMapNum == 2) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[2])) {
			//MovingCamera[3] = true;
			MovingCamera[2] = true;
			MapOn[3] = true;
		}
	}

	// ##### 2 <-- 3  #####
	if (CurrMapNum == 3) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[2])) {
			//MovingCamera[3] = true;
			MovingCamera[2] = true;
			MapOn[2] = true;
		}
	}


	// ##### 3 --> 4  #####
	if (CurrMapNum == 3) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[3])) {
			//MovingCamera[4] = true;
			MovingCamera[3] = true;
			MapOn[4] = true;
		}
	}

	// ##### 3 <-- 4  #####
	if (CurrMapNum == 4) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[3])) {
			//MovingCamera[4] = true;
			MovingCamera[3] = true;
			MapOn[3] = true;
		}
	}


	// ##### 4 --> 5  #####
	if (CurrMapNum == 4) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[4])) {
			//MovingCamera[5] = true;
			MovingCamera[4] = true;
			MapOn[5] = true;
		}
	}

	// ##### 4 <-- 5  #####
	if (CurrMapNum == 5) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[4])) {
			//MovingCamera[5] = true;
			MovingCamera[4] = true;
			MapOn[4] = true;
		}
	}


	// ##### 5 --> 6  #####
	if (CurrMapNum == 5) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[5])) {
			//MovingCamera[6] = true;
			MovingCamera[5] = true;
			MapOn[6] = true;
		}
	}

	//// ##### 5 <-- 6  #####
	if (CurrMapNum == 6) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[5])) {
			//MovingCamera[6] = true;
			MovingCamera[5] = true;
			MapOn[5] = true;
		}
	}


	// ##### 6 --> 7  #####
	if (CurrMapNum == 6) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[6])) {
			//MovingCamera[7] = true;
			MovingCamera[6] = true;
			MapOn[7] = true;
		}
	}

	//// ##### 6 <-- 7  #####
	if (CurrMapNum == 7) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[6])) {
			//MovingCamera[7] = true;
			MovingCamera[6] = true;
			MapOn[6] = true;
		}
	}

	// ##### 7 --> 8  #####
	if (CurrMapNum == 7) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[7])) {
			//MovingCamera[8] = true;
			MovingCamera[7] = true;
			MapOn[8] = true;
		}
	}

	//// ##### 7 <-- 8  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[7])) {
			//MovingCamera[8] = true;
			MovingCamera[7] = true;
			MapOn[7] = true;
		}
	}

	// ##### 8 --> 9  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[8])) {
			//MovingCamera[9] = true;
			MovingCamera[8] = true;
			MapOn[9] = true;
		}
	}

	//// ##### 9 <-- 8  #####
	if (CurrMapNum == 9) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[8])) {
			//MovingCamera[9] = true;
			MovingCamera[8] = true;
			MapOn[8] = true;
		}
	}


	// ##### 8 --> 10  #####
	if (CurrMapNum == 8) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[9])) {
			MovingCamera[9] = true;
			//MovingCamera[8] = true;
			MapOn[10] = true;
		}
	}

	// ##### 12 --> 13  #####
	if (CurrMapNum == 12) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[12])) {
			MovingCamera[12] = true;
			MapOn[13] = true;
		}
	}


	// ##### 13 --> 14  #####
	if (CurrMapNum == 13) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[13])) {
			MovingCamera[13] = true;
			MapOn[14] = true;
		}
	}

	//// ##### 13 <-- 14  #####
	if (CurrMapNum == 14) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[13])) {
			MovingCamera[13] = true;
			MapOn[13] = true;
		}
	}


	// ##### 13 --> 15 #####
	if (CurrMapNum == 13) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[14])) {
			MovingCamera[14] = true;
			MapOn[15] = true;
		}
	}


	// ##### 15 --> 16 #####
	if (CurrMapNum == 15) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[15])) {
			MovingCamera[15] = true;
			MapOn[16] = true;
		}
	}

	//// ##### 15 <-- 16  #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[15])) {
			MovingCamera[15] = true;
			MapOn[15] = true;
		}
	}

	// ##### 15 --> 16 #####
	if (CurrMapNum == 15) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[16])) {
			MovingCamera[15] = true;
			MapOn[16] = true;
		}
	}

	//// ##### 15 <-- 16  #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[16])) {
			MovingCamera[15] = true;
			MapOn[15] = true;
		}
	}


	// ##### 16 --> 17 #####
	if (CurrMapNum == 16) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[17])) {
			MovingCamera[16] = true;
			MapOn[17] = true;
		}
	}

	
	// ##### 17 --> 18 #####
	if (CurrMapNum == 17) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[18])) {
			MovingCamera[17] = true;
			MapOn[18] = true;
		}
	}


	// ##### 18 --> 19 #####
	if (CurrMapNum == 18) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[19])) {
			MovingCamera[18] = true;
			MapOn[19] = true;
		}
	}

	// ##### 19 --> 20 #####
	if (CurrMapNum == 19) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[20])) {
			MovingCamera[19] = true;
			MapOn[20] = true;
		}
	}

	// ##### 20 --> 21 #####
	if (CurrMapNum == 20) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[21])) {
			MovingCamera[20] = true;
			MapOn[21] = true;
		}
	}

	// ##### 21 --> 23 #####
	if (CurrMapNum == 21) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[22])) {
			MovingCamera[21] = true;
			MapOn[22] = true;
		}
	}

	// ##### 23 --> 24 #####
	if (CurrMapNum == 22) {
		RECT rc;
		if (IntersectRect(&rc, &m_pPlayerLink->getPlayerRect(), &CheckChangeMapRect[23])) {
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
			if (1620 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 1600) {
				m_Camera.x = 1600;
				CurrMapNum = 1;
				MovingCamera[0] = false;
				MapOn[0] = false;
			}
		}
	}

	// ##### 0 <-- 1  #####
	if (CurrMapNum == 1 && MovingCamera[0] == true) {
		if (m_Camera.x > 1203) {
			m_Camera.x -= 6;
			if (1565 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 1203) {
				CurrMapNum = 0;
				MovingCamera[0] = false;
				MapOn[1] = false;
			}
		}
	}


	// ##### 1 --> 2  #####
	if (MovingCamera[1] == true && CurrMapNum == 1) {
		if (m_Camera.x < 2000) {
			m_Camera.x += 6;
			if (2004 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2000) {
				m_Camera.x = 2000;
				CurrMapNum = 2;
				MovingCamera[1] = false;
				MapOn[1] = false;
			}
		}
	}

	// ##### 1 <-- 2  #####
	if (CurrMapNum == 2 && MovingCamera[1] == true) {
		if (m_Camera.x > 1600) {
			m_Camera.x -= 6;
			if (1973 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 1600) {
				CurrMapNum = 1;
				MovingCamera[1] = false;
				MapOn[2] = false;
			}
		}
	}


	// ##### 2 --> 3  #####
	if (MovingCamera[2] == true && CurrMapNum == 2) {
		if (m_Camera.y > 426) {
			m_Camera.y -= 5;
			if (580 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 426) {
				m_Camera.y = 424;
				CurrMapNum = 3;
				MovingCamera[2] = false;
			}
		}
	}

	// ##### 2 <-- 3  #####
	if (MovingCamera[2] == true && CurrMapNum == 3) {
		if (m_Camera.y < 634) {
			m_Camera.y += 5;
			if (620 > m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() + 0.9f);
			}
			if (m_Camera.y >= 634) {
				m_Camera.y = 634;
				CurrMapNum = 2;
				MovingCamera[2] = false;
				MapOn[3] = false;
			}
		}
	}


	// ##### 3 --> 4  #####
	if (MovingCamera[3] == true && CurrMapNum == 3) {
		if (m_Camera.x < 2400) {
			m_Camera.x += 6;
			if (2410 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2400) {
				CurrMapNum = 4;
				MovingCamera[3] = false;
			}
		}
	}

	// ##### 3 <-- 4  #####
	if (MovingCamera[3] == true && CurrMapNum == 4) {
		if (m_Camera.x > 2000) {
			m_Camera.x -= 6;
			if (2350 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 2000) {
				MapOn[4] = false;
				CurrMapNum = 3;
				MovingCamera[3] = false;
			}
		}
	}


	// ##### 4 --> 5  #####
	if (MovingCamera[4] == true && CurrMapNum == 4) {
		if (m_Camera.x < 2800) {
			m_Camera.x += 6;
			if (2810 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2800) {
				m_Camera.x = 2800;
				CurrMapNum = 5;
				MovingCamera[4] = false;
			}
		}
	}

	// ##### 4 <-- 5  #####
	if (MovingCamera[4] == true && CurrMapNum == 5) {
		if (m_Camera.x > 2400) {
			m_Camera.x -= 6;
			if (2760 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 2400) {
				MapOn[5] = false;
				CurrMapNum = 4;
				MovingCamera[4] = false;
			}
		}
	}



	// ##### 5 --> 6  #####
	if (MovingCamera[5] == true && CurrMapNum == 5) {
		if (m_Camera.y < 634) {
			m_Camera.y += 5;
			if (670 > m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() + 0.9f);
			}
			if (m_Camera.y >= 634) {
				m_Camera.y = 634;
				CurrMapNum = 6;
				MovingCamera[5] = false;
				MapOn[5] = false;
			}
		}
	}

	// ##### 5 <-- 6  #####
	if (MovingCamera[5] == true && CurrMapNum == 6) {
		if (m_Camera.y > 426) {
			m_Camera.y -= 5;
			if (580 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 426) {
				m_Camera.y = 426;
				CurrMapNum = 5;
				MovingCamera[5] = false;
				MapOn[6] = false;
			}
		}
	}

	// ##### 6 --> 7  #####
	if (MovingCamera[6] == true && CurrMapNum == 6) {
		if (m_Camera.y < 842) {
			m_Camera.y += 5;
			if (863 > m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() + 0.9f);
			}
			if (m_Camera.y >= 842) {
				m_Camera.y = 842;
				CurrMapNum = 7;
				MovingCamera[6] = false;
				MapOn[6] = false;
			}
		}
	}

	// ##### 7 --> 8  #####
	if (MovingCamera[7] == true && CurrMapNum == 7) {
		if (m_Camera.y < 1050) {
			m_Camera.y += 5;
			if (1070 > m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() + 0.9f);
			}
			if (m_Camera.y >= 1050) {
				m_Camera.y = 1050;
				CurrMapNum = 8;
				MovingCamera[7] = false;
				MapOn[7] = false;
			}
		}
	}

	
	// ##### 8 --> 9  #####
	if (MovingCamera[8] == true && CurrMapNum == 8) {
		if (m_Camera.x > 2400) {
			m_Camera.x -= 6;
			if (2760 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 2400) {
				m_Camera.x = 2400;
				CurrMapNum = 9;
				MovingCamera[8] = false;
				MapOn[8] = false;
			}
		}
	}

	// ##### 8 <-- 9  #####
	if (MovingCamera[8] == true && CurrMapNum == 9) {
		if (m_Camera.x < 2800) {
			m_Camera.x += 6;
			if (2810 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 2800) {
				m_Camera.x = 2800;
				CurrMapNum = 8;
				MovingCamera[8] = false;
				MapOn[9] = false;
			}
		}
	}


	// ##### 8 --> 10  #####
	if (MovingCamera[9] == true && CurrMapNum == 8) {
		if (m_Camera.x < 3200) {
			m_Camera.x += 6;
			if (3240 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 3200) {
				m_Camera.x = 3200;
				CurrMapNum = 12;
				MovingCamera[9] = false;
				MapOn[8] = false;
			}
		}
	}

	
	// ##### 12 --> 13  #####
	if (MovingCamera[12] == true && CurrMapNum == 12) {
		if (m_Camera.y > 842) {
			m_Camera.y -= 5;
			if (995 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 842) {
				m_Camera.y = 842;
				m_Camera.x = 4000;
				CurrMapNum = 13;
				MovingCamera[12] = false;
				MapOn[10] = false;
			}
		}
	}


	// ##### 13 --> 14  #####
	if (MovingCamera[13] == true && CurrMapNum == 13) {
		if (m_Camera.x < 4400) {
			m_Camera.x += 6;
			if (4600 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 4400) {
				m_Camera.x = 4400;
				CurrMapNum = 14;
				MovingCamera[13] = false;
				MapOn[13] = false;
			}
		}
	}

	// ##### 13 <-- 14  #####
	if (MovingCamera[13] == true && CurrMapNum == 14) {
		if (m_Camera.x > 4000) {
			m_Camera.x -= 6;
			if (4365 < m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() - 0.5f);
			}
			if (m_Camera.x <= 4000) {
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
			if (785 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 634) {
				m_Camera.y = 634;
				CurrMapNum = 15;
				MovingCamera[14] = false;
				MapOn[13] = false;
			}
		}
	}


	// ##### 15 --> 16  #####
	if (MovingCamera[15] == true && CurrMapNum == 15) {
		if (m_Camera.y > 426) {
			m_Camera.y -= 5;
			if (360 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 426) {
				m_Camera.y = 426;
				CurrMapNum = 16;
				MovingCamera[15] = false;
				MapOn[15] = false;
			}
		}
	}

	// ##### 15 <-- 16  #####
	if (MovingCamera[15] == true && CurrMapNum == 16) {
		if (m_Camera.y < 634) {
			m_Camera.y += 5;
			if (660 > m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() + 0.9f);
			}
			if (m_Camera.y >= 634) {
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
			if (4600 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 4400) {
				m_Camera.x = 4400;
				CurrMapNum = 17;
				MovingCamera[16] = false;
				MapOn[16] = false;
			}
		}
	}


	// ##### 17 --> 18  #####
	if (MovingCamera[17] == true && CurrMapNum == 17) {
		if (m_Camera.x < 5200) {
			m_Camera.x += 6;
			if (5250 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 5200) {
				m_Camera.x = 5200;
				CurrMapNum = 18;
				MovingCamera[17] = false;
				MapOn[17] = false;
			}
		}
	}

	// ##### 18 --> 19  #####
	if (MovingCamera[18] == true && CurrMapNum == 18) {
		if (m_Camera.x < 5600) {
			m_Camera.x += 6;
			if (5650 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 5600) {
				m_Camera.x = 5600;
				CurrMapNum = 19;
				MovingCamera[18] = false;
				MapOn[18] = false;
			}
		}
	}

	// ##### 19 --> 20  #####
	if (MovingCamera[19] == true && CurrMapNum == 19) {
		if (m_Camera.y > 218) {
			m_Camera.y -= 5;
			if (150 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 218) {
				m_Camera.y = 218;
				CurrMapNum = 20;
				MovingCamera[19] = false;
				MapOn[19] = false;
			}
		}
	}


	// ##### 20 --> 21  #####
	if (MovingCamera[20] == true && CurrMapNum == 20) {
		if (m_Camera.y > 10) {
			m_Camera.y -= 5;
			if (0 < m_pPlayerLink->getPlayerY()) {
				m_pPlayerLink->SetPlayerY(m_pPlayerLink->getPlayerY() - 0.9f);
			}
			if (m_Camera.y <= 10) {
				m_Camera.y = 10;
				CurrMapNum = 21;
				MovingCamera[20] = false;
				MapOn[20] = false;
			}
		}
	}


	// ##### 21 --> 22  #####
	if (MovingCamera[21] == true && CurrMapNum == 21) {
		if (m_Camera.x < 6000) {
			m_Camera.x += 6;
			if (6050 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 6000) {
				m_Camera.x = 6000;
				CurrMapNum = 22;
				MovingCamera[21] = false;
				MapOn[21] = false;
			}
		}
	}

	// ##### 22 --> 23  #####
	if (MovingCamera[22] == true && CurrMapNum == 22) {
		if (m_Camera.x < 6400) {
			m_Camera.x += 6;
			if (6450 > m_pPlayerLink->getPlayerX()) {
				m_pPlayerLink->SetPlayerX(m_pPlayerLink->getPlayerX() + 0.5f);
			}
			if (m_Camera.x >= 6400) {
				m_Camera.x = 6400;
				CurrMapNum = 23;
				MovingCamera[22] = false;
				MapOn[22] = false;
			}
		}
	}
}

MapManager::MapManager() : m_pPlayerLink(NULL), m_Camera({ 0 , 0 }),  _empty(new image)
{
}


MapManager::~MapManager()
{
}
