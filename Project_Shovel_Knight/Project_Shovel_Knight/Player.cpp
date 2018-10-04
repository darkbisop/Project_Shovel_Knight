#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_nrightCount = 0;
	m_nleftCount = 0;
	State = P_IDLE;
	//m_bIsAppear = true;

	m_startimg = IMAGEMANAGER->addImage("appear", "image/Player/Player_appear.bmp", 540, 51, 9, 1, true, RGB(255, 0, 255));
	m_img = IMAGEMANAGER->addImage("idle_right", "image/Player/Player_idle_right.bmp", 34, 32, true, RGB(255, 0, 255));
	m_moveimg = IMAGEMANAGER->addImage("walk", "image/Player/Player_move.bmp", 240, 70, 6, 2, true, RGB(255, 0, 255));
	m_attackimg = IMAGEMANAGER->addImage("attack", "image/Player/Player_attack.bmp", 270, 70, 5, 2, true, RGB(255, 0, 255));
	m_jumpimg = IMAGEMANAGER->addImage("jump_right", "image/Player/Player_jump_right.bmp", 31, 34, true, RGB(255, 0, 255));
	m_jumpdownimg = IMAGEMANAGER->addImage("jump_down_right", "image/Player/Player_rightdown.bmp", 33, 34, true, RGB(255, 0, 255));
	m_jumpatkimg = IMAGEMANAGER->addImage("jumpatk_right", "image/Player/Player_jumpattck_right.bmp", 24, 36, true, RGB(255, 0, 255));
	m_magicimg = IMAGEMANAGER->addImage("magic_right", "image/Player/Player_magic.bmp", 84, 64, 2, 2, true, RGB(255, 0, 255));
	m_ballimg = IMAGEMANAGER->addImage("Magic_fireball", "image/Player/Magic_fireball.bmp", 26, 13, 2, 1, true, RGB(255, 0, 255));
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
	Money = 10000;
	
	//m_rc = RectMake(m_fX, m_fY, m_img->getWidth(), m_img->getHeight());

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
	m_inventory->update();
	m_Equipment->update();

	State = P_IDLE;

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		m_bIsAttck = true;
	}
	if (KEYMANAGER->isOnceKeyDown('K') && m_bIsjump == false)
	{
		m_bIsjump = true;
		m_bIsjumpAtk = false;
		Jumpspeed = 5.5f;

		/*Jumpspeed += 4.0f;
		if (Jumpspeed > 0.1f) {
			State = P_JUMP;
		}*/
	}

	if (m_bIsjump == true && KEYMANAGER->isOnceKeyDown('S'))
	{
		m_bIsjumpAtk = true;
	}

	if (KEYMANAGER->isStayKeyDown('A') /*&& m_fX >= 0*/)
	{
		m_bIsAttck = false;
		State = P_MOVELEFT;
		m_nCurrFrameY = 1;
		if (m_moveimg)
		{
			m_nCount++;
			if (m_nCount % 7 == 0)
			{
				m_nCurrFrameX++;
				m_moveimg->setFrameX(m_nCurrFrameX);
				if (m_nCurrFrameX > m_moveimg->getMaxFrameX())
				{
					m_nCurrFrameX = 0;
				}
			}
		}
		m_fX -= m_fSpeed;
		m_img = IMAGEMANAGER->addImage("idle_left", "image/Player/Player_idle_left.bmp", 34, 32, true, RGB(255, 0, 255));
		m_jumpimg = IMAGEMANAGER->addImage("jump_left", "image/Player/Player_jump_left.bmp", 31, 34, true, RGB(255, 0, 255));
		m_magicimg = IMAGEMANAGER->addImage("magic_left", "image/Player/Player_magic.bmp", 84, 64, 2, 2, true, RGB(255, 0, 255));
		if (Jumpspeed - gravity <= 0)
		{
			m_jumpdownimg = IMAGEMANAGER->addImage("jump_down_left", "image/Player/Player_leftdown.bmp", 33, 34, true, RGB(255, 0, 255));
		}
		if (State == P_MOVELEFT && m_bIsjumpAtk == true)
		{
			m_jumpatkimg = IMAGEMANAGER->addImage("jumpatk_left", "image/Player/Player_jumpattck_left.bmp", 24, 36, true, RGB(255, 0, 255));
		}
	}
	else if (KEYMANAGER->isStayKeyDown('D') /*&& (m_fX + m_img->getWidth() <= WINSIZEX)*/)
	{
		m_bIsAttck = false;
		State = P_MOVERIGHT;
		m_nCurrFrameY = 0;
		if (m_moveimg)
		{
			m_nCount++;
			if (m_nCount % 7 == 0)
			{
				m_nCurrFrameX++;
				m_moveimg->setFrameX(m_nCurrFrameX);
				if (m_nCurrFrameX > m_moveimg->getMaxFrameX())
				{
					m_nCurrFrameX = 0;
				}
			}
		}
		m_fX += m_fSpeed;
		m_img = IMAGEMANAGER->addImage("idle_right", "image/Player/Player_idle_right.bmp", 34, 32, true, RGB(255, 0, 255));
		m_jumpimg = IMAGEMANAGER->addImage("jump_right", "image/Player/Player_jump_right.bmp", 31, 34, true, RGB(255, 0, 255));
		m_magicimg = IMAGEMANAGER->addImage("magic_right", "image/Player/Player_magic.bmp", 84, 64, 2, 2, true, RGB(255, 0, 255));
		if (Jumpspeed - gravity <= 0)
		{
			m_jumpdownimg = IMAGEMANAGER->addImage("jump_down_right", "image/Player/Player_rightdown.bmp", 33, 34, true, RGB(255, 0, 255));
		}
		if (m_bIsjumpAtk == true)
		{
			m_jumpatkimg = IMAGEMANAGER->addImage("jumpatk_right", "image/Player/Player_jumpattck_right.bmp", 24, 36, true, RGB(255, 0, 255));
		}
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

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		v_Iter->gravity += 0.1f;
		v_Iter->x += cosf(75 * 3.14 / 180) * v_Iter->speed;
		v_Iter->y -= sinf(v_Iter->angle) * v_Iter->speed - v_Iter->gravity;
		v_Iter->rc = RectMake(v_Iter->x, v_Iter->y, 5, 5);
	}

	Attack();
	Move();
	m_rc = RectMake(m_fX + 5, m_fY, 20, 25);
}

void Player::render(HDC hdc)
{
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//Rectangle(hdc, m_InvenRect.left, m_InvenRect.top, m_InvenRect.right, m_InvenRect.bottom);

	//Rectangle(hdc, m_Floor.left, m_Floor.top, m_Floor.right, m_Floor.bottom);

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
	}

	if (State == P_APPEAR)
	{
		m_startimg->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
	}
	else if (State == P_IDLE)
	{
		if (m_nCurrFrameY == 0)
		{
			m_img->render(hdc, m_fX, m_fY - 7);
		}
		if (m_nCurrFrameY == 1)
		{
			m_img->render(hdc, m_fX - 5, m_fY - 7);
		}
	}
	if (State == P_MOVERIGHT || State == P_MOVELEFT)
	{
		if (m_nCurrFrameY == 0)
		{
			m_moveimg->frameRender(hdc, m_fX, m_fY - 8, m_nCurrFrameX, m_nCurrFrameY);
		}
		if (m_nCurrFrameY == 1)
		{
			m_moveimg->frameRender(hdc, m_fX - 10, m_fY - 8, m_nCurrFrameX, m_nCurrFrameY);
		}
	}
	if (State == P_ATTACK)
	{
		if (m_nCurrFrameY == 0)
		{
			m_attackimg->frameRender(hdc, m_fX, m_fY - 7, m_nCurrFrameX, m_nCurrFrameY);
		}
		if (m_nCurrFrameY == 1)
		{
			m_attackimg->frameRender(hdc, m_fX - 15, m_fY - 7, m_nCurrFrameX, m_nCurrFrameY);
		}
	}
	if (State == P_JUMP)
	{
		if (m_bIsjumpAtk == false)
		{
			if (Jumpspeed - gravity > -1.4f)
			{
				m_jumpimg->render(hdc, m_fX, m_fY - 8);
			}
			else if (Jumpspeed - gravity <= -1.4f)
			{
				m_jumpdownimg->render(hdc, m_fX, m_fY - 8);
			}
		}
		if (State == P_ATTACK && State == P_JUMP)
		{
			if (m_nCurrFrameY == 0)
			{
				m_attackimg->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
			}
			if (m_nCurrFrameY == 1)
			{
				m_attackimg->frameRender(hdc, m_fX - 15, m_fY, m_nCurrFrameX, m_nCurrFrameY);
			}
		}
		else if (m_bIsjumpAtk == true)
		{
			m_jumpatkimg->render(hdc, m_fX, m_fY);
		}
	}
	if (State == P_MAGIC)
	{
		if (m_nCurrFrameY == 0)
		{
			m_magicimg->frameRender(hdc, m_fX, m_fY, m_nCurrFrameX, m_nCurrFrameY);
		}
		if (m_nCurrFrameY == 1)
		{
			m_magicimg->frameRender(hdc, m_fX - 15, m_fY, m_nCurrFrameX, m_nCurrFrameY);
		}
	}

	m_UI->render(hdc, MAPMANAGER->getCamera().x, MAPMANAGER->getCamera().y);
	m_inventory->render(hdc);
	m_Equipment->render(m_UI->getMemDC());

	char str[64];
	//wsprintf(str, "money : %d", m_bIsjump);
	sprintf_s(str, "x : %f, y : %f", m_fX, m_fY);
	TextOut(hdc, 100, 100, str, strlen(str));
}

void Player::Attack()
{
	if (m_bIsAttck == true)
	{
		State = P_ATTACK;
		m_nCurrFrameY = 0;
		if (m_img == IMAGEMANAGER->addImage("idle_right", "image/Player_idle_right.bmp", 34, 32, true, RGB(255, 0, 255)))
		{
			m_nCurrFrameY = 0;
			if (m_attackimg)
			{
				m_nrightCount++;
				if (m_nrightCount % 4 == 0)
				{
					m_nCurrFrameX++;
					m_attackimg->setFrameX(m_nCurrFrameX);
					if (m_nCurrFrameX > m_attackimg->getMaxFrameX())
					{
						m_bIsAttck = false;
						m_nCurrFrameX = 0;
						m_nrightCount = 0;
					}
				}
			}
		}
		if (m_img == IMAGEMANAGER->addImage("idle_left", "image/Player_idle_left.bmp", 34, 32, true, RGB(255, 0, 255)))
		{
			m_nCurrFrameY = 1;
			if (m_attackimg)
			{
				m_nleftCount++;
				if (m_nleftCount % 4 == 0)
				{
					m_nCurrFrameX++;
					m_attackimg->setFrameX(m_nCurrFrameX);
					if (m_nCurrFrameX > m_attackimg->getMaxFrameX())
					{
						m_bIsAttck = false;
						m_nCurrFrameX = 0;
						m_nleftCount = 0;
					}
				}
				if (m_bIsAttck == false)
				{
					m_nCurrFrameX = 0;
					m_nleftCount = 0;
				}
			}
		}
	}
}

void Player::Move()
{
	if (m_bIsjump == true)
	{
		State = P_JUMP;
		gravity += 0.2f;
		m_fY -= Jumpspeed - gravity;
	}
	/*else {
		gravity += 0.2f;
		m_fY -= Jumpspeed - gravity;
	}*/

	/*if (m_bIsjump == false) {
		gravity += 0.3f;
		m_fY -= Jumpspeed - gravity;

		if (gravity > Jumpspeed) {
			State = P_JUMP;
		}
	}*/
}

void Player::RectColliosion(RECT x)
{
	RECT rc;
	if (IntersectRect(&rc, &m_rc, &x)) {
		if (m_rc.right - 5 < x.left + 10) {
			m_fX -= 2.0f;
			State = P_IDLE;
		}

		else if (m_rc.left + 5 > x.right - 10) {
			m_fX += 2.0f;
			State = P_IDLE;
		}

		/*else if (m_rc.bottom > x.bottom) {
			m_bIsjump = false;
			gravity = 0;
			Jumpspeed = 0;
			m_rc.top = x.bottom;
			m_rc.bottom = m_rc.top + 25;
			State = P_IDLE;
		}
*/
		else if (m_rc.bottom > x.top) {
			m_bIsjump = false;
			gravity = 0;
			Jumpspeed = 0;
			m_fY = x.top - 25;
			State = P_IDLE;
		}
	}
}

Player::Player() : Money(10000)
{
}


Player::~Player()
{
}
