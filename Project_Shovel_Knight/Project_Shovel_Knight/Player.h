#pragma once
#include "singletonBase.h"
#include "Equipment.h"
#include "Inventory.h"

struct FireBall
{
	float x, y;
	RECT rc;
	float angle;
};

enum State
{
	P_APPEAR, P_IDLE, P_MOVE, P_ATTACK, P_DOWNATTACK, P_MAGIC, P_JUMP, P_LADDERUP, P_LADDERSTOP, P_DAMAGED, P_DEAD, P_INVISIBLE
};

class Player : public singletonBase<Player>
{
private:

	vector<FireBall> v_Bullet;
	vector<FireBall>::iterator v_IterBullet;

	Inventory*	m_inventory;
	Equipment*	m_Equipment;
	FireBall m_bullet;

	RECT	m_rc;
	RECT	m_AttackRc;
	RECT	m_AttackDownRc;
	State	m_State;

	image*	m_UI;
	image*	m_IdleImg;
	image*	m_MoveImg;
	image*	m_JumpImg;
	image*	m_JumpDown;
	image*	m_AttackImg;
	image*	m_AttackDownImg;
	image*	m_LadderUpImg;
	image*	m_DamagedImg;
	image*	m_AppearImg;
	image*	m_DeathImg;
	image*	m_InvisibleImg;
	

	image*	m_Number_1;
	image*	m_Number_2;
	image*	m_Number_3;
	image*	m_Number_4;

	image*	m_HpBar1;
	image*	m_HpBar2;
	image*	m_HpBar3;
	image*	m_HpBar4;
	image*	m_HpBar5;
	image*	m_HpKAn;

	int		m_CurrFrameX;
	int		m_CurrFrameY;
	int		m_FrameCount;
	int		m_AtkFrameCount;
	int		m_AttackCount;
	int		m_DEADCount;

	float	m_fSpeed;
	float	m_fX;
	float	m_fY;

	float	gravity;
	float	jumpSpeed;

	bool	m_isRight;
	bool	m_isAttack;
	bool	m_isGround;
	bool	m_invincibleTime;
	bool	m_isDamaged;
	bool	m_isAppear;
	bool	m_isFalling;
	bool	m_isDead;
	bool	m_isInvisible;

	bool	m_isMovingMap;
	bool	m_isCheck;
	bool	m_isDeadCHeck;
	bool	m_isAfterLoad;
	bool	m_isFireLeft;

	bool	m_EquipFlameWand;
	bool	m_EquipInvi;
	bool	m_isPlusHp;
	
	int		Money;
	int		Hp;
	int		Mana;
	int		m_DamagedTime;
	int		m_AppearTime;
	int		m_invincibleCount;
	int		m_invincibleAlpha;

public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void KeyProcess();
	void Animation();
	void FireBallMove();
	void ShovelRender(HDC hdc);
	void RectColliosion(RECT x);
	void LadderColliosion(RECT x);
	void SpikeColliosion(RECT x);
	void SaveColliosion(RECT x);
	void DownATKCollision(RECT x);
	void DownATKtoOBJCollision(RECT x);
	void OBJCollision(RECT x);
	void UIrender(HDC hdc);

	inline RECT getPlayerRect() { return m_rc; }
	inline RECT getAttacRect() { return m_AttackRc; }
	inline RECT getAttacDWRect() { return m_AttackDownRc; }

	inline State getState() { return m_State; }
	inline void setState(State a) { m_State = a; }

	inline float getPlayerX() { return m_fX; }
	inline float getPlayerY() { return m_fY; }

	inline void SetPlayerX(float x) { m_fX = x; }
	inline void SetPlayerY(float y) { m_fY = y; }

	inline int getMoney() { return Money; }
	inline void setMoney(int a) { Money = a; }

	inline bool getIsAfterLoad() { return m_isAfterLoad; }
	inline void setIsAfterLoad(bool a) { m_isAfterLoad = a; }

	inline bool getIsMovingMap() { return m_isMovingMap; }
	inline void setIsMovingMap(bool a) { m_isMovingMap = a; }

	inline int getHP() { return Hp; }
	inline void setHp(int a) { Hp = a; }

	inline void setAppear(bool a) { m_isAppear = a; }

	inline bool getInvincibleTime() { return m_invincibleTime; }
	inline void setInvincibleTime(bool a) { m_invincibleTime = a; }

	inline bool getIsDamaged() { return m_isDamaged; }
	inline void setIsDamaged(bool a) { m_isDamaged = a; }

	inline bool getEquipFlameWand() { return m_EquipFlameWand; }
	inline void setEquipFlameWand(bool a) { m_EquipFlameWand = a; }

	inline bool getEquipInvi() { return m_EquipInvi; }
	inline void setEquipInvi(bool a) { m_EquipInvi = a; }

	inline Inventory* getInventory() { return m_inventory; }

	Player();
	~Player();
};

