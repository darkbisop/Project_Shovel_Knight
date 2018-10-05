#pragma once
#include "scene.h"
#include "enemyManager.h"

class PlayScene : public scene
{
private:

	// �� �� �ϼ��ϰ� ���� ����ٰ� ��, ���ʹ� �� ��� ó�� �Ұ���. ���߿� �ּ� Ǯ��
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

