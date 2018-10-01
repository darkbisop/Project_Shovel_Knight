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
	
}

void Player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	m_PlayerImg->render(hdc, m_fX, m_fY);
	//m_FrontMap->render(hdc, 0, 430);
}

Player::Player()
{
}


Player::~Player()
{
}
