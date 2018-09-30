#pragma once
#include "scene.h"

class Player;
class MapImage;

class RunAndGunScene : public scene
{
private:

	MapImage* m_pMapImage;
	Player * m_pPlayerLink;
	POINT	m_Camera;

	image*	_empty;
	image*	m_UI;
	
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
	void CurrMap();
	void CollisionCheck_ChangeMapRect();
	void MovingMap();

	RunAndGunScene();
	~RunAndGunScene();
};

