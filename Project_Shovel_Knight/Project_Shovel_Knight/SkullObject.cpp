#include "stdafx.h"
#include "SkullObject.h"


HRESULT SkullObject::init(float x, float y)
{
	m_Img = IMAGEMANAGER->addImage("skeleton_head(R)", "image/Object/skeleton_head(R).bmp", 12, 12, true, RGB(255, 0, 255));

	m_fX = x;
	m_fY = y;
	m_angle = _angle;
	m_gravity = _gravity;
	_isAlive = true;
	_Count = 0;
	MoveRight = false;
	MoveLeft = false;
	return S_OK;
}

void SkullObject::release()
{
}

void SkullObject::update()
{
	RECT rc;
	if (IntersectRect(&rc, &PLAYER->getAttacRect(), &_rc)) {
		if (m_fX < PLAYER->getPlayerX()) MoveLeft = true;
		else if (m_fX > PLAYER->getPlayerX()) MoveRight = true;
	}

	if (MoveRight) {
		m_gravity += 0.1f;
		if (m_gravity > 0.1f) {
			m_fX += cosf(20) * 3.0f;
			m_fY -= sinf(40) * 3.0f - m_gravity;
			_rc = RectMake(m_fX, m_fY, 12, 12);
		}
	}

	if (MoveLeft) {
		m_gravity += 0.1f;
		if (m_gravity > 0.1f) {

			m_fX -= cosf(20) * 3.0f;
			m_fY -= sinf(40) * 3.0f - m_gravity;
			_rc = RectMake(m_fX, m_fY, 12, 12);
		}
	}
	
	for (int i = 0; i < MAPMANAGER->getMapVectorRcSize(); i++) {
		if (IntersectRect(&rc, &_rc, &MAPMANAGER->getMapVectorRc(i))) {

			if (_rc.right < MAPMANAGER->getMapVectorRc(i).left + 4) {
				if (MoveRight && m_gravity > 0.1f) {
					MoveRight = false;
					m_gravity = 0;
					MoveLeft = true;
				}
			}

			else if (_rc.left > MAPMANAGER->getMapVectorRc(i).right - 4) {
				if (MoveLeft && m_gravity > 0.1f) {
					MoveLeft = false;
					m_gravity = 0;
					MoveRight = true;
				}

			}

			else {
				m_gravity = 0;
				m_fY = MAPMANAGER->getMapVectorRc(i).top - 12;
				MoveRight = false;
				MoveLeft = false;
			}
		}
	}

	_rc = RectMake(m_fX, m_fY, 12, 12);
}

void SkullObject::render(HDC hdc)
{
	//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
	m_Img->render(hdc, m_fX, m_fY);
}

SkullObject::SkullObject()
{
}


SkullObject::~SkullObject()
{
}
