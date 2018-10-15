#pragma once
class enemyInfo // enemy들의 부모 클래스
{
protected:
	RECT	m_rc;			// enemy에 대한 rect

	// 상태별 이미지 로드
	image*	m_pImg_Idle;
	image*	m_pImg_Move;
	image*	m_pImg_Atk;
	image*	m_pImg_Hit;
	image*	m_pImg_Die;

	int		m_nLife;		// 체력
	int		m_nPower;		// 공격력
	int		m_nFireCount;	// 발사 카운트
	int		m_nEffectCount;	// 이펙트 카운트

	float	m_fX;			// 위치 X
	float	m_fY;			// 위치 Y
	float	m_fSpeed;		// 속도 변수
	float	m_fRange;		// 범위 변수
	float	m_fAngle;		// 각도
	float	m_fJumpSpeed;	// 점프 스피드
	float	m_fGravity;		// 중력 값

	bool	m_isAlive;		// 적이 죽었는지 확인 할 변수
	bool	m_isDamage;		// 공격을 당했을 때를 확인 할 변수
	bool	m_isMove;		// 무브인 상태를 확인 할 변수
	bool	m_isDying;		// 죽는 모션을 나타내기 위한 변수
	bool	m_isRight;		// 오른쪽으로 이동하는지 확인 할 변수
	bool	m_isFire;		// 발사했는지 확인 할 변수

	// === 이미지별 프레임 === //

	// idle
	int		m_nCurrFrameX_Idle;
	int		m_nCurrFrameY_Idle;
	int		m_nFrameCount_Idle;

	// move
	int		m_nCurrFrameX_Move;
	int		m_nCurrFrameY_Move;
	int		m_nFrameCount_Move;

	// atk
	int		m_nCurrFrameX_Atk;
	int		m_nCurrFrameY_Atk;
	int		m_nFrameCount_Atk;

	// hit
	int		m_nCurrFrameX_Hit;
	int		m_nCurrFrameY_Hit;
	int		m_nFrameCount_Hit;

	// die
	int		m_nCurrFrameX_Die;
	int		m_nCurrFrameY_Die;
	int		m_nFrameCount_Die;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline RECT getRect() { return m_rc; }

	inline float getX() { return m_fX; }
	inline void setX(float _fX) { m_fX = _fX; }

	inline float getY() { return m_fY; }
	inline void setY(float _fY) { m_fY = _fY; }

	inline bool	getIsAlive() { return m_isAlive; }
	inline void setIsAlive(float _isAlive) { m_isAlive = _isAlive; }

	enemyInfo();
	virtual ~enemyInfo();
};

