#pragma once
class enemyInfo // enemy���� �θ� Ŭ����
{
protected:
	RECT	m_rc;			// enemy�� ���� rect

	// ���º� �̹��� �ε�
	image*	m_pImg_Idle;
	image*	m_pImg_Move;
	image*	m_pImg_Atk;
	image*	m_pImg_Hit;
	image*	m_pImg_Die;

	int		m_nLife;		// ü��
	int		m_nPower;		// ���ݷ�
	int		m_nFireCount;	// �߻� ī��Ʈ
	int		m_nEffectCount;	// ����Ʈ ī��Ʈ

	float	m_fX;			// ��ġ X
	float	m_fY;			// ��ġ Y
	float	m_fSpeed;		// �ӵ� ����
	float	m_fRange;		// ���� ����
	float	m_fAngle;		// ����
	float	m_fJumpSpeed;	// ���� ���ǵ�
	float	m_fGravity;		// �߷� ��

	bool	m_isAlive;		// ���� �׾����� Ȯ�� �� ����
	bool	m_isDamage;		// ������ ������ ���� Ȯ�� �� ����
	bool	m_isMove;		// ������ ���¸� Ȯ�� �� ����
	bool	m_isDying;		// �״� ����� ��Ÿ���� ���� ����
	bool	m_isRight;		// ���������� �̵��ϴ��� Ȯ�� �� ����
	bool	m_isFire;		// �߻��ߴ��� Ȯ�� �� ����

	// === �̹����� ������ === //

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

