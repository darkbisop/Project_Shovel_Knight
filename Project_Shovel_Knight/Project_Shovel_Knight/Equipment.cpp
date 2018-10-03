#include "stdafx.h"
#include "Equipment.h"


HRESULT Equipment::init(void)
{
	/*for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++)
	{
		m_Equipment[i]._type = (Item_Type)i;
	}
*/
	m_Equipment[ITEM_WEAPON]._rect = RectMake(66, 3, 13, 13);
	m_Equipment[ITEM_WEAPON]._item = NULL;

	return S_OK;
}

void Equipment::release(void)
{
	for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++)
	{
		SAFE_DELETE(m_Equipment[i]._item);
	}
}

void Equipment::update(void)
{
}

void Equipment::render(HDC hdc)
{
	for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++)
	{
		//Rectangle(hdc, m_Equipment[i]._rect.left, m_Equipment[i]._rect.top, m_Equipment[i]._rect.right, m_Equipment[i]._rect.bottom);

		if (m_Equipment[i]._item != NULL) {
			m_Equipment[i]._item->getImage()->render(hdc, m_Equipment[i]._rect.left, m_Equipment[i]._rect.top);
		}
	}
}

Item * Equipment::setEquipment(Item * item)
{
	Item* equip = m_Equipment[item->getType()]._item;
	m_Equipment[item->getType()]._item = item;
	setItemEffect();
	return equip;
}

void Equipment::setItemEffect()
{
	for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++) {
		if (m_Equipment[i]._item != NULL) {
			if (m_Equipment[i]._item->getType() == ITEM_WEAPON) {
				// 여기다 지팡이 착용했을때 총알 발사하기
				PLAYER->setMMM(true);
			}
		}
	}
}

Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}
