#pragma once
#include "singletonBase.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "Shop.h"

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

	enemyManager *	m_pEnemyMgr;
	effectManager*	m_pEffectMgr;
	objectManager*	m_pObjectMgr;
	MapImage*		m_pMapImage;
	Shop*			m_Shop;

	POINT	m_Camera;

	image*	_empty;
	image*	m_SkyBg;
	image*	BackGround_Castle;
	image*	Back_3_Ground;
	image*	Back_2_Ground;
	image*	Back_Ground;
	image*  m_pImg;
	image*  m_shopBg;
	image*	m_Screen;
	image*	m_ScreenRvs;
	
	RECT	CheckChangeMapRect[25];

	int		CurrMapNum;
	int		m_FrameCount;
	int		m_CurrFrameX;
	int		m_ReverseFrameX;
	
	bool	MovingCamera[24];
	bool	MapOn[24];
	bool	ScreenSFXOn;
	bool	ScreenSFXREV;

	char m_szText[64];
	char m_szText2[64];
	char m_szText3[64];
	char m_szText4[64];

	vector<string> vec;
	vector<std::string> m_vecLoad;
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

	void CollisionMap();
	void CollisionEnemy();
	void CollisionBoss();
	void CollisionObject();
	void ScreenEffect();

	RECT getMapVectorRc(int i) { return vRect.at(i)._rc; }
	int getMapVectorRcSize() { return vRect.size(); }

	RECT getLadderVECRc(int i) { return vLadderRect.at(i)._rc; }
	int getLadderVECRcSize() { return vLadderRect.size(); }

	inline bool getMapNum() { return CurrMapNum; }
	inline bool getMapOn(int x) { return MapOn[x]; }

	inline void setCameraX(int a) { m_Camera.x = a; }
	inline void setCameraY(int a) { m_Camera.y = a; }

	MapManager();
	~MapManager();
};

