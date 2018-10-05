#pragma once
#include "singletonBase.h"

struct tagMapInfo
{
	RECT _rc;
};

struct MapLadder
{
	RECT _rc;
};

class MapImage;

class MapManager : public singletonBase<MapManager>
{
private:

	tagMapInfo _RectInfo;
	vector<tagMapInfo> vRect;
	vector<tagMapInfo>::iterator vIterRC;

	MapLadder  _RectLadder;
	vector<MapLadder> vLadderRect;
	vector<MapLadder>::iterator vIterLDRRC;

	MapImage* m_pMapImage;
	POINT	m_Camera;

	image*	_empty;
	image*	m_SkyBg;
	image*	BackGround_Castle;
	image*	Back_3_Ground;
	image*	Back_2_Ground;
	image*	Back_Ground;
	
	RECT	CheckChangeMapRect[24];
	RECT	m_Floor;

	int		CurrMapNum;
	
	bool	MovingCamera[24];
	bool	MapOn[24];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	POINT getCamera() { return m_Camera; }

	//void setPlayerLink(Player* player) { m_pPlayerLink = player; }
	void CheckMapRect();
	void CurrMap();
	void CollisionCheck_ChangeMapRect();
	void MovingMap();
	void PushRect();
	void EraseRect(int i);

	RECT getMapVectorRc(int i) { return vRect.at(i)._rc; }
	int getMapVectorRcSize() { return vRect.size(); }

	RECT getLadderVECRc(int i) { return vLadderRect.at(i)._rc; }
	int getLadderVECRcSize() { return vLadderRect.size(); }

	inline bool getMapNum() { return CurrMapNum; }

	MapManager();
	~MapManager();
};

