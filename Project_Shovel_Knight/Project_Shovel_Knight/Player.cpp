#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{
	m_PlayerImg = IMAGEMANAGER->addImage("space", "image/Player_idle_right.bmp", 34, 32, true, RGB(255, 0, 255));
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
	
	m_rc = RectMake(m_fX, m_fY, 26, 30);
	m_InvenRect = RectMake(m_invenX, m_invenY, 223, 20);
	
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

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		m_fX += m_fSpeed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		m_fX -= m_fSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		m_fY -= m_fSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		m_fY += m_fSpeed;
	}

	if (KEYMANAGER->isOnceKeyDown('S')) {
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

	m_rc = RectMake(m_fX, m_fY, 20, 30);
}

void Player::render(HDC hdc)
{
	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//Rectangle(hdc, m_InvenRect.left, m_InvenRect.top, m_InvenRect.right, m_InvenRect.bottom);

	for (v_Iter = v_VecTemp.begin(); v_Iter != v_VecTemp.end(); v_Iter++) {
		Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
	}

	m_PlayerImg->render(hdc, m_fX, m_fY);

	m_UI->render(hdc, MAPMANAGER->getCamera().x, MAPMANAGER->getCamera().y);
	m_inventory->render(hdc);
	m_Equipment->render(m_UI->getMemDC());

	/*char str[64];
	wsprintf(str, "money : %d", m_isMoving);
	TextOut(hdc, m_fX, m_fY, str, strlen(str));*/
}

Player::Player() : Money(10000)
{
}


Player::~Player()
{
}
