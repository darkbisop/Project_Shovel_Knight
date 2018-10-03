#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "Equipment.h"

HRESULT Inventory::init(void)
{
	m_InventoryImg = IMAGEMANAGER->addImage("Inventory", "image/Item/Inventory.bmp", 223, 143, true, RGB(255, 0, 255));
	m_SelectImg = IMAGEMANAGER->addImage("SelectIcon", "image/Item/SelectIcon.bmp", 32, 32, true, RGB(255, 0, 255));

	m_rc = RectMake(WINSIZEX / 2 - 100, WINSIZEY / 2 - 37, 223, 60);
	Money = 10000;

	m_fx = WINSIZEX / 2 - 86;
	m_fy = WINSIZEY / 2 - 39;

	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			m_Inventory[y][x].m_pItem = NULL;
			m_Inventory[y][x]._rect = RectMake(m_rc.left + 20 + x * 33, m_rc.top + 4 + y * 36, 13, 13);
		}
	}

	m_InvenY = 0;
	invenOn = false;

	return S_OK;
}

void Inventory::release(void)
{
	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			SAFE_DELETE(m_Inventory[y][x].m_pItem);
		}
	}
}

void Inventory::update(void)
{
	RECT rc;
	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			if (IntersectRect(&rc, &Select_Rect, &m_Inventory[y][x]._rect) && m_Inventory[y][x].m_pItem != NULL) {
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
					m_Inventory[y][x].m_pItem = m_pEquipment->setEquipment(m_Inventory[y][x].m_pItem);
				}
			}
		}
	}

	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			if (IntersectRect(&rc, &Select_Rect, &m_Inventory[y][x]._rect) && m_Inventory[y][x].m_pItem != NULL) {
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
					PLAYER->setMoney(PLAYER->getMoney() + m_Inventory[y][x].m_pItem->getCost() / 2);
					sellItem(x, y);
				}
			}
		}
	}

	if (invenOn == false && KEYMANAGER->isOnceKeyDown('E')) {
		invenOn = true;
	}
	else if (invenOn == true && KEYMANAGER->isOnceKeyDown('E')) {
		invenOn = false;
		m_InvenY = 0;
	}

	if (invenOn) {
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			if (m_rc.right - 70 > m_fx) m_fx += 33.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			if (m_rc.left + 35 < m_fx) m_fx -= 33.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
			if (m_rc.bottom - 35 > m_fy) m_fy += 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
			if (m_rc.top < m_fy) m_fy -= 35.0f;
		}

		if (m_InvenY < 143) {
			m_InvenY += 19;
		}
		if (m_InvenY >= 143) {
			m_InvenY = 143;
		}
	}

	Select_Rect = RectMake(m_fx, m_fy, 25, 25);
}

void Inventory::render(HDC hdc)
{
	if (invenOn) {
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		//Rectangle(hdc, Select_Rect.left, Select_Rect.top, Select_Rect.right, Select_Rect.bottom);
		m_InventoryImg->render(hdc, m_rc.left, m_rc.top - 35, 223, m_InvenY);
		m_SelectImg->render(hdc, Select_Rect.left, Select_Rect.top, 25, 25);

		for (int y = 0; y < INVENTORY_Y; y++) {
			for (int x = 0; x < INVENTORY_X; x++) {
				//Rectangle(hdc, m_Inventory[y][x]._rect.left, m_Inventory[y][x]._rect.top, m_Inventory[y][x]._rect.right, m_Inventory[y][x]._rect.bottom);
				if (m_Inventory[y][x].m_pItem) {
					m_Inventory[y][x].m_pItem->getImage()->render(hdc, m_Inventory[y][x]._rect.left, m_Inventory[y][x]._rect.top);
				}
			}
		}
	}

	
}

void Inventory::buyItem(Item * item)
{
	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			if (m_Inventory[y][x].m_pItem == NULL) {
				m_Inventory[y][x].m_pItem = item;
				PLAYER->setMoney(PLAYER->getMoney() - m_Inventory[y][x].m_pItem->getCost());
				return;
			}
		}
	}
}

void Inventory::sellItem(int x, int y)
{
	SAFE_DELETE(m_Inventory[y][x].m_pItem);
}

void Inventory::setItem(Item * item)
{
	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			if (m_Inventory[y][x].m_pItem == NULL) {
				m_Inventory[y][x].m_pItem = item;
				return;
			}
		}
	}
}

bool Inventory::isEmpty()
{
	for (int y = 0; y < INVENTORY_Y; y++) {
		for (int x = 0; x < INVENTORY_X; x++) {
			if (m_Inventory[y][x].m_pItem == NULL) {
				return true;
			}
		}
	}
	return false;
}

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
