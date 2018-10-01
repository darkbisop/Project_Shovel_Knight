#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{
	m_PlayerImg = IMAGEMANAGER->addImage("space", "image/Player_idle_right.bmp", 34, 32, true, RGB(255, 0, 255));
	
	m_fX = 30;
	m_fY = 720;

	m_fSpeed = 2.0f;

	m_rc = RectMake(m_fX, m_fY, 26, 30);

	m_State = Player_State::IDLE;
	m_isMoving = false;
	tempRan = 0;

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	m_rc = RectMake(m_fX + 3, m_fY, 20, 30);
	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		Player_State::MOVE;
		m_fX += m_fSpeed;
		m_isMoving = true;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		Player_State::MOVE;
		m_fX -= m_fSpeed;
		m_isMoving = true;
	}
	else m_isMoving = false;

	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		Player_State::MOVE;
		m_fY -= m_fSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		Player_State::MOVE;
		m_fY += m_fSpeed;
	}
	
	
	if (KEYMANAGER->isOnceKeyDown('S')) {
		tempRan = RANDOM->getFromIntTo(3, 6);
		for (int i = 0; i < tempRan; i++) {
			m_Drop.x = m_fX + 22;
			m_Drop.y = m_fY + 27;
			m_Drop.gravity = 0;
			m_Drop.angle = RANDOM->getFromFloatTo(1.0f, 1.9f);
			m_Drop.speed = RANDOM->getFromFloatTo(2.1f, 3.5f);
			v_VecTemp.push_back(m_Drop);
		}
	}

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		v_Iter->gravity += 0.1f;
		v_Iter->x += cosf(80 * 3.14 / 180) * v_Iter->speed;
		v_Iter->y -= sinf(v_Iter->angle) * v_Iter->speed - v_Iter->gravity;
		v_Iter->rc = RectMake(v_Iter->x, v_Iter->y, 5, 5);
	}
}

void Player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
	}

	m_PlayerImg->render(hdc, m_fX, m_fY);
	//m_FrontMap->render(hdc, 0, 430);
}

Player::Player()
{
}


Player::~Player()
{
}
