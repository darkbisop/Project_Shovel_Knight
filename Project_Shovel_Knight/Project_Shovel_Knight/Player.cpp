#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{
	//m_startimg = IMAGEMANAGER->addImage("appear", "image/Player/Player_appear.bmp", 540, 51, 9, 1, true, RGB(255, 0, 255));
	m_IdleImg = IMAGEMANAGER->addImage("Player_Idle", "image/Player/Player_Idle.bmp", 34, 64, 1, 2, true, RGB(255, 0, 255));
	m_MoveImg = IMAGEMANAGER->addImage("Player_move", "image/Player/Player_move.bmp", 240, 70, 6, 2, true, RGB(255, 0, 255));
	m_AttackImg = IMAGEMANAGER->addImage("Player_attack", "image/Player/Player_attack.bmp", 270, 70, 5, 2, true, RGB(255, 0, 255));
	m_JumpImg = IMAGEMANAGER->addImage("Player_jump_right", "image/Player/Player_jump_right.bmp", 31, 34, true, RGB(255, 0, 255));
	m_JumpLeftImg = IMAGEMANAGER->addImage("Player_jump_left", "image/Player/Player_jump_left.bmp", 31, 34, true, RGB(255, 0, 255));
	m_AttackDownImg = IMAGEMANAGER->addImage("Player_jumpattck_right", "image/Player/Player_jumpattck_right.bmp", 24, 36, true, RGB(255, 0, 255));
	m_DownLeftImg = IMAGEMANAGER->addImage("Player_jumpattck_left", "image/Player/Player_jumpattck_left.bmp", 24, 36, true, RGB(255, 0, 255));
	m_JumpDown = IMAGEMANAGER->addImage("Player_rightdown", "image/Player/Player_rightdown.bmp", 33, 34, true, RGB(255, 0, 255));
	m_JumpDownLeft = IMAGEMANAGER->addImage("Player_leftdown", "image/Player/Player_leftdown.bmp", 33, 34, true, RGB(255, 0, 255));
	
	m_UI = IMAGEMANAGER->addImage("UI", "image/UI.bmp", 400, 18, true, RGB(255, 0, 255));

	m_inventory = new Inventory;
	m_inventory->init();

	m_Equipment = new Equipment;
	m_Equipment->init();

	m_inventory->SetEquipmentLink(m_Equipment);
	m_Equipment->setInventoryLink(m_inventory);

	m_fX = 30;
	m_fY = 720;
	m_fSpeed = 2.0f;
	jumpSpeed = 0;
	gravity = 0;
	Money = 10000;
	
	m_FrameCount = 0;
	m_CurrFrameX = 0;
	m_CurrFrameY = 0;
	m_AtkFrameCount = 0;

	m_isRight = true;
	m_isAttack = false;
	m_isAirAttack = false;
	m_isGround = false;

	m_State = P_IDLE;

	tempRan = 0;
	
	return S_OK;
}

void Player::release()
{
	m_inventory->release();
	SAFE_DELETE(m_inventory);

	m_Equipment->release();
	SAFE_DELETE(m_Equipment);
}

void Player::update()
{
	m_FrameCount++;
	m_inventory->update();
	m_Equipment->update();

	KeyProcess();
	Animation();

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		v_Iter->gravity += 0.1f;
		v_Iter->x += cosf(75 * 3.14 / 180) * v_Iter->speed;
		v_Iter->y -= sinf(v_Iter->angle) * v_Iter->speed - v_Iter->gravity;
		v_Iter->rc = RectMake(v_Iter->x, v_Iter->y, 5, 5);
	}

	if (m_isGround == false) {
		gravity += 9.8f / 60.0f;
		m_fY -= jumpSpeed - gravity;
	}

	m_rc = RectMake(m_fX + 5, m_fY, 20, 25);
}

void Player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
	}

	ShovelRender(hdc);

	m_UI->render(hdc, MAPMANAGER->getCamera().x, MAPMANAGER->getCamera().y);
	m_inventory->render(hdc);
	m_Equipment->render(m_UI->getMemDC());

	//char str[64];
	//wsprintf(str, "money : %d", m_isGround);
	////sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	//TextOut(hdc, m_fX, m_fY, str, strlen(str));
}

void Player::KeyProcess()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		if (m_State != P_JUMP && m_State != P_MOVERIGHT) {
			m_State = P_ATTACK;
		}
		if (m_State != P_JUMP) {
			m_State = P_MOVERIGHT;
			m_isAirAttack = false;
		}

		m_fX += m_fSpeed;
		m_isRight = true;
	}

	else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		if (m_State != P_JUMP && m_State != P_MOVELEFT) {
			m_State = P_ATTACK;
		}

		if (m_State != P_JUMP) {
			m_State = P_MOVELEFT;
			m_isAirAttack = false;
		}

		m_fX -= m_fSpeed;
		m_isRight = false;
	}

	if (KEYMANAGER->isOnceKeyDown('C') && gravity <= 0) {
		jumpSpeed += 5.0f;
		if (jumpSpeed > 0.1f) {
			m_State = P_JUMP;
			m_isGround = false;
		}
	}

	if (jumpSpeed > 1.0f && KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		m_State = P_DOWNATTACK;
	}

	if (KEYMANAGER->isOnceKeyDown('X')) {
		m_State = P_ATTACK;
		m_isAttack = true;
	}
	

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_isRight == true) {
		m_State = P_IDLE;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_isRight == false) {
		m_State = P_IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		tempRan = RANDOM->getFromIntTo(3, 6);
		for (int i = 0; i < tempRan; i++) {
			m_Drop.x = m_fX + 22;
			m_Drop.y = m_fY + 27;
			m_Drop.gravity = 0;
			m_Drop.angle = RANDOM->getFromFloatTo(1.0f, 1.9f);
			m_Drop.speed = RANDOM->getFromFloatTo(2.5f, 3.5f);
			v_VecTemp.push_back(m_Drop);
		}
	}
}

void Player::Animation()
{
	if (m_State == P_MOVERIGHT && m_isRight == true) {
		m_FrameCount++;
		
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_MoveImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX > m_MoveImg->getMaxFrameX()) {
				m_CurrFrameX = 0;
			}
		}
	}

	else if (m_State == P_MOVELEFT && m_isRight == false) {
		m_FrameCount++;
		m_CurrFrameY = 1;
		if (m_FrameCount % 7 == 0) {
			m_CurrFrameX++;
			m_MoveImg->setFrameX(m_CurrFrameX);

			if (m_CurrFrameX > m_MoveImg->getMaxFrameX()) {
				m_CurrFrameX = 0;
			}
		}
	}

	if (m_isAttack) {
		m_State = P_ATTACK;
		if (m_isRight == true) {
			m_CurrFrameY = 0;
			m_FrameCount++;
			if (m_FrameCount % 5 == 0) {
				m_AtkFrameCount++;
				m_AttackImg->setFrameX(m_AtkFrameCount);

				if (m_AtkFrameCount > m_AttackImg->getMaxFrameX()) {
					m_AtkFrameCount = 0;
					m_isAttack = false;
					m_State = P_IDLE;
				}
			}
		}
		else if (m_isRight == false) {
			m_CurrFrameY = 1;
			m_FrameCount++;
			if (m_FrameCount % 5 == 0) {
				m_AtkFrameCount++;
				m_AttackImg->setFrameX(m_AtkFrameCount);

				if (m_AtkFrameCount > m_AttackImg->getMaxFrameX()) {
					m_AtkFrameCount = 0;
					m_isAttack = false;
					m_State = P_IDLE;
				}
			}
		}
	}
}

void Player::ShovelRender(HDC hdc)
{
	if (m_State == P_IDLE) {
		if (m_isRight) m_IdleImg->frameRender(hdc, m_fX, m_fY - 7, 0, 0);
		else if (!m_isRight) m_IdleImg->frameRender(hdc, m_fX - 2, m_fY - 7, 0, 1);
	}
	
	else if (m_State == P_MOVERIGHT && m_isRight == true) {
		m_MoveImg->frameRender(hdc, m_fX, m_fY - 7, m_CurrFrameX, 0);
	}

	else if (m_State == P_MOVELEFT && m_isRight == false) {
		m_MoveImg->frameRender(hdc, m_fX - 8, m_fY - 7, m_CurrFrameX, 1);
	}
	
	else if (m_isAttack) {
		if (m_isRight) m_AttackImg->frameRender(hdc, m_fX, m_fY - 7, m_AtkFrameCount, m_CurrFrameY);
		else if (!m_isRight) m_AttackImg->frameRender(hdc, m_fX - 19, m_fY - 7, m_AtkFrameCount, m_CurrFrameY);
	}

	else if (m_State == P_JUMP) {
		if (m_isRight) {
			if (jumpSpeed - gravity >= 0)m_JumpImg->render(hdc, m_fX - 3, m_fY - 8);
			else if (jumpSpeed - gravity <= 0) m_JumpDown->render(hdc, m_fX, m_fY - 8);
		}
		else if (!m_isRight) {
			if (jumpSpeed - gravity >= 0)m_JumpLeftImg->render(hdc, m_fX, m_fY - 8);
			else if (jumpSpeed - gravity <= 0) m_JumpDownLeft->render(hdc, m_fX - 3, m_fY - 8);
		}
	}

	else if (m_State == P_DOWNATTACK) {
		if (m_isRight) m_AttackDownImg->render(hdc, m_fX + 2, m_fY - 8);
		else if (!m_isRight) m_DownLeftImg->render(hdc, m_fX + 2, m_fY - 8);
	}
}

void Player::RectColliosion(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {

		if (m_rc.right - 5 < x.left + 10) {
			m_fX -= 2.0f;
			m_State = P_IDLE;
		}

		else if (m_rc.left + 5 > x.right - 10) {
			m_fX += 2.0f;
			m_State = P_IDLE;

		}

		else if (m_rc.bottom > x.bottom + 10) {
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = false;
			m_rc.top = x.bottom;
			m_rc.bottom = m_rc.top + 25;
		}
		else if (m_rc.bottom > x.top) {
			m_State = P_IDLE;
			m_fY = x.top - 24;
			gravity = 0;
			jumpSpeed = 0;
			m_isGround = true;
		}
	}

	else m_isGround = false;
}

void Player::LadderColliosion(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {
		gravity = 0;
		jumpSpeed = 0;
		m_isGround = true;

		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			m_fX = x.left - 12;
			m_fY -= m_fSpeed;
		}

		else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			m_fX = x.left - 12;
			m_fY += m_fSpeed;
		}

		
	}

	if (KEYMANAGER->isOnceKeyDown('C') && gravity <= 0) {
		m_isGround = false;
		jumpSpeed += 5.0f;
		if (jumpSpeed > 0.1f) {
			m_State = P_JUMP;
			
		}
	}
}

Player::Player() : Money(10000)
{
}


Player::~Player()
{
}
