#pragma once
#include "scene.h"
#include "enemyManager.h"

class PlayScene : public scene
{
private:

	// 맵 다 완성하고 나면 여기다가 맵, 에너미 및 모든 처리 할거임. 나중에 주석 풀기
	//enemyManager * m_pEnemyMgr;


	//image*	_empty;
	//image*	m_SkyBg;
	//image*	BackGround_Castle;
	//image*	Back_3_Ground;
	//image*	Back_2_Ground;
	//image*	Back_Ground;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void PlayerMapCollision();
	void DrawMap();

	PlayScene();
	~PlayScene();
};

