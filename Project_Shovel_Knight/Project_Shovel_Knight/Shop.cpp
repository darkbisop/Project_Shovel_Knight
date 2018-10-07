#include "stdafx.h"
#include "Shop.h"
#include "Flame_Wand.h"
#include "Inventory.h"

HRESULT Shop::init(void)
{
	m_rc = RectMake(WINSIZEX / 2 - 100, 30, 223, 60);

	v_Item_List.push_back(new Flame_Wand);

	ShopOn = false;

	m_fx = WINSIZEX / 2 - 90;
	m_fy = 30;

	return S_OK;
}

void Shop::release(void)
{
	while (v_Item_List.size() > 0) {
		SAFE_DELETE((*v_Item_List.begin()));
		v_Item_List.erase(v_Item_List.begin());
	}
}

void Shop::update(void)
{
	if (ShopOn == false && KEYMANAGER->isOnceKeyDown('S')) {
		ShopOn = true;
	}

	else if (ShopOn == true && KEYMANAGER->isOnceKeyDown('S')) {
		ShopOn = false;
	}

	if (ShopOn) {
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			if (m_rc.right - 70 > m_fx) m_fx += 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			if (m_rc.left + 35 < m_fx) m_fx -= 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
			if (m_rc.bottom - 55 > m_fy) m_fy += 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
			if (m_rc.top < m_fy) m_fy -= 35.0f;
		}
	}

	RECT rc;
	if (ShopOn == true) {
		for (int i = 0; i < v_Item_List.size(); i++) {
			ItemListRect = RectMake(m_rc.left + 16 + i, m_rc.top + 6 + i * 70, 13, 13);

			if (IntersectRect(&rc, &ItemListRect, &MoveRect)) {
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
					Item* item = new Item;
					*item = *v_Item_List[i];
					m_Inventory->buyItem(item);
				}
			}
		}
	}

	MoveRect = RectMake(m_fx, m_fy, 25, 25);
}

void Shop::render(HDC hdc)
{
	if (ShopOn == true) {
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		Rectangle(hdc, MoveRect.left, MoveRect.top, MoveRect.right, MoveRect.bottom);
		
		for (int i = 0; i < v_Item_List.size(); i++) {
			Rectangle(hdc, ItemListRect.left, ItemListRect.top, ItemListRect.right, ItemListRect.bottom);
			v_Item_List[i]->getImage()->render(hdc, ItemListRect.left, ItemListRect.top);
		}
	}

	char str[64];
	wsprintf(str, "money : %d", PLAYER->getMoney());
	//sprintf_s(str, "x : %f", m_fX, m_fY);
	TextOut(hdc, 100, 170, str, strlen(str));
}

Shop::Shop()
{
}


Shop::~Shop()
{
}
