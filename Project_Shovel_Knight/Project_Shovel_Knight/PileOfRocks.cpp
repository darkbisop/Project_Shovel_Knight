#include "stdafx.h"
#include "PileOfRocks.h"


HRESULT PileOfRocks::init(float x, float y)
{
	m_fX = x;
	m_fY = y;
	m_angle = _angle;
	m_gravity = _gravity;
	_isAlive = true;

	_Count = 5;
	RanD = 0;

	return S_OK;
}

void PileOfRocks::release()
{
}

void PileOfRocks::update()
{
	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		v_Iter->gravity += 0.1f;
		if (v_Iter->gravity > 0.1f) {
			v_Iter->x += cosf(75 * 3.14 / 180) * v_Iter->speed;
			v_Iter->y -= sinf(v_Iter->angle) * v_Iter->speed - v_Iter->gravity;
			v_Iter->isAlive = true;
			v_Iter->rc = RectMake(v_Iter->x, v_Iter->y, 5, 5);
		}
	}

	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		RECT rc;
		for (int i = 0; i < MAPMANAGER->getMapVectorRcSize(); i++) {
			if (IntersectRect(&rc, &v_Iter->rc, &MAPMANAGER->getMapVectorRc(i))) {
				v_Iter->gravity = 0;
				v_Iter->y = MAPMANAGER->getMapVectorRc(i).top - 20;
			}

			if (IntersectRect(&rc, &v_Iter->rc, &PLAYER->getPlayerRect())) {
				v_Iter->isAlive = false;
			}
		}
	}

	_rc = RectMake(m_fX, m_fY, 20, 20);
}

void PileOfRocks::render(HDC hdc)
{
	if (_isAlive) Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);

	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		if (v_Iter->isAlive) Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
	}

	//char str[64];
	//wsprintf(str, "money : %d", _Count);
	//////sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	//TextOut(hdc, m_fX, m_fY, str, strlen(str));
}

void PileOfRocks::DigOut()
{
	_Count--;

	if (_Count >= 0) {
		RanD = RANDOM->getFromIntTo(3, 6);
		for (int i = 0; i < RanD; i++) {
			m_Drop.x = m_fX + 17;
			m_Drop.y = m_fY + 10;
			m_Drop.gravity = 0;
			m_Drop.angle = RANDOM->getFromFloatTo(1.0f, 1.9f);
			m_Drop.speed = RANDOM->getFromFloatTo(2.5f, 3.5f);
			v_VecJewel.push_back(m_Drop);
		}
	}
	
	if (_Count <= 0) _isAlive = false;
}

PileOfRocks::PileOfRocks()
{
}


PileOfRocks::~PileOfRocks()
{
}
