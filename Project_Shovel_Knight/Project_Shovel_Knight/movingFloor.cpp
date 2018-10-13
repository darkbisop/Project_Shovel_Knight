#include "stdafx.h"
#include "movingFloor.h"


HRESULT movingFloor::init(float x, float y, float rangeX, float rangeY, bool Right, bool up, bool moveRight, bool moveUp, float speed)
{
	m_img = IMAGEMANAGER->addImage("MovingFloor", "image/Object/MovingFloor.bmp", 48, 16, true, RGB(255, 0, 255));
	m_fX = x;
	m_fY = y;

	m_fSpeed = speed;

	_rc = RectMakeCenter(m_fX, m_fY, 48, 16);
	m_rangeRC = RectMakeCenter(m_fX, m_fY, rangeX, rangeY);

	m_isRight = Right;
	m_isUp = up;

	m_upMove = moveUp;
	m_rightMove = moveRight;

	return S_OK;
}

void movingFloor::release()
{
}

void movingFloor::update()
{
	if (m_rightMove == true) {
		if (_rc.left < m_rangeRC.left) {
			m_isRight = true;
		}
		if (_rc.right > m_rangeRC.right) {
			m_isRight = false;
		}
		if (m_isRight) {
			m_fX += m_fSpeed;
			m_fY += 0;
			_rc = RectMakeCenter(m_fX, m_fY, 48, 16);
		}
		else if (!m_isRight) {
			m_fX -= m_fSpeed;
			m_fY += 0;
			_rc = RectMakeCenter(m_fX, m_fY, 48, 16);
		}
	}

	if (m_upMove == true) {
		if (_rc.top < m_rangeRC.top) {
			m_isUp = false;
		}
		if (_rc.bottom > m_rangeRC.bottom) {
			m_isUp = true;
		}
		if (m_isUp) {
			m_fX += 0;
			m_fY -= m_fSpeed;
			_rc = RectMakeCenter(m_fX, m_fY, 48, 16);
		}
		else if (!m_isUp) {
			m_fX -= 0;
			m_fY += m_fSpeed;
			_rc = RectMakeCenter(m_fX, m_fY, 48, 16);
		}
	}
}

void movingFloor::render(HDC hdc)
{		
	Rectangle(hdc, m_rangeRC.left, m_rangeRC.top, m_rangeRC.right, m_rangeRC.bottom);
	//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
	m_img->render(hdc, _rc.left, _rc.top);
}

movingFloor::movingFloor()
{
}


movingFloor::~movingFloor()
{
}
