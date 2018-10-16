#include "stdafx.h"
#include "Shop.h"
#include "Inventory.h"
#include "Flame_Wand.h"
#include "TempItem.h"

HRESULT Shop::init(void)
{
	m_shopIMG = IMAGEMANAGER->addImage("ShopArr", "image/Item/ShopArr.bmp", 400, 89, true, RGB(255, 0, 255));
	m_Select = IMAGEMANAGER->addImage("itemSelect", "image/Item/itemSelect.bmp", 30, 28, true, RGB(255, 0, 255));
	
	m_rc = RectMake(83, 15, 142, 59);

	v_Item_List.push_back(new Flame_Wand);
	v_Item_List.push_back(new TempItem);

	ShopOn = false;

	m_fx = 86;
	m_fy = 15;

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
		PLAYER->setIsMovingMap(true);
	}

	else if (ShopOn == true && KEYMANAGER->isOnceKeyDown('S')) {
		ShopOn = false;
		PLAYER->setIsMovingMap(false);
	}

	if (ShopOn) {
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
			if (m_rc.right - 40 > m_fx) m_fx += 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
			if (m_rc.left + 10 < m_fx) m_fx -= 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
			if (m_rc.bottom - 36 > m_fy) m_fy += 35.0f;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
			if (m_rc.top < m_fy) m_fy -= 35.0f;
		}
	}

	RECT rc;
	if (ShopOn == true) {
		for (int i = 0; i < v_Item_List.size(); i++) {
			ItemListRect = RectMake(m_rc.left + 8 + i * 35, m_rc.top + 6, 13, 13);

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
	
		m_shopIMG->render(hdc, 0, 0);
		m_Select->render(hdc, m_fx, m_fy);
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		//Rectangle(hdc, MoveRect.left, MoveRect.top, MoveRect.right, MoveRect.bottom);

		for (int i = 0; i < v_Item_List.size(); i++) {
			ItemListRect = RectMake(m_rc.left + 12 + i * 35, m_rc.top + 6, 13, 13);
			//Rectangle(hdc, ItemListRect.left, ItemListRect.top, ItemListRect.right, ItemListRect.bottom);
			v_Item_List[i]->getImage()->render(hdc, ItemListRect.left, ItemListRect.top);
		}
	}

	//char str[64];
	//wsprintf(str, "money : %d", PLAYER->getMoney());
	////sprintf_s(str, "x : %f", m_fX, m_fY);
	//TextOut(hdc, 100, 170, str, strlen(str));
}

Shop::Shop()
{
}


Shop::~Shop()
{
}
