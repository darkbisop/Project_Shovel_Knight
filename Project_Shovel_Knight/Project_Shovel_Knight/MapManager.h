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

struct saveRect
{
	RECT _rc;
	bool SaveCheck;
	int m_CheckSaveFrame;
};

struct SpikeRect
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

	saveRect  _RectSave;
	vector<saveRect> vSaveRect;
	vector<saveRect>::iterator vIterSaveRC;

	SpikeRect  _RectSpike;
	vector<SpikeRect> vSpikeRect;
	vector<SpikeRect>::iterator vIterSpikeRC;

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
	image*	m_SaveCheckPoint;

	RECT	CheckChangeMapRect[25];
	
	int		CurrMapNum;
	int		m_FrameCount;
	int		m_CurrFrameX;
	int		m_ReverseFrameX;
	int		m_CheckSaveFrame;
	int		m_screenFrame;
	
	bool	MovingCamera[24];
	bool	MapOn[24];
	bool	ScreenSFXOn;
	bool	ScreenSFXREV;
	bool	ScreenSFXREV2;
	bool	SaveCheck;

	char m_szText[128];
	char m_szText2[128];
	char m_szText3[128];
	char m_szText4[128];

	bool	m_ScreenRVS;
	int		m_ScreenRVSFrame;

	vector<string> vec;
	vector<std::string> m_vecLoad;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	POINT getCamera() { return m_Camera; }

	void CheckMapRect();
	void CurrMap();
	void CollisionCheck_ChangeMapRect();
	void MovingMap();
	void PushRect();
	void ScreenEffect();
	void SavePoint();
	void LoadPoint();

	void CollisionMap();
	void CollisionEnemy();
	void CollisionBoss();
	void CollisionObject();

	RECT getMapVectorRc(int i) { return vRect.at(i)._rc; }
	int getMapVectorRcSize() { return vRect.size(); }

	RECT getLadderVECRc(int i) { return vLadderRect.at(i)._rc; }
	int getLadderVECRcSize() { return vLadderRect.size(); }

	RECT getSaveVECRc(int i) { return vSaveRect.at(i)._rc; }
	int getSaveVECRcSize() { return vSaveRect.size(); }

	RECT getSpikeVECRc(int i) { return vSpikeRect.at(i)._rc; }
	int getSpikeVECRcSize() { return vSpikeRect.size(); }

	inline void setCheckOn(bool a) { SaveCheck = a; }
	inline bool getCheckOn() { return SaveCheck; }

	inline bool getMapNum() { return CurrMapNum; }
	inline bool getMapOn(int x) { return MapOn[x]; }

	inline bool getSceenSFX() { return ScreenSFXOn; }
	inline void setSceenSFX(bool a) { ScreenSFXOn = a; }

	inline void setCameraX(int a) { m_Camera.x = a; }
	inline void setCameraY(int a) { m_Camera.y = a; }

	MapManager();
	~MapManager();
};

