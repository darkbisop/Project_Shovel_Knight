#pragma once
#include "singletonBase.h"

class Player;
class MapImage;

class MapManager : public singletonBase<MapManager>
{
private:

	MapImage* m_pMapImage;
	Player * m_pPlayerLink;
	POINT	m_Camera;

	image*	_empty;
	image*	m_UI;
	image*	m_SkyBg;
	image*	BackGround_Castle;
	image*	Back_3_Ground;
	image*	Back_2_Ground;
	image*	Back_Ground;
	
	RECT	CheckChangeMapRect[24];

	int		CurrMapNum;
	
	bool	MovingCamera[24];
	bool	MapOn[24];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	POINT getCamera() { return m_Camera; }

	void setPlayerLink(Player* player) { m_pPlayerLink = player; }
	void CheckMapRect();
	void CurrMap();
	void CollisionCheck_ChangeMapRect();
	void MovingMap();

	MapManager();
	~MapManager();
};

