#include "stdafx.h"
#include "Equipment.h"


HRESULT Equipment::init(void)
{
	/*for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++)
	{
		m_Equipment[i]._type = (Item_Type)i;
	}
*/
	m_Equipment[ITEM_EQUIP]._rect = RectMake(66, 3, 13, 13);
	m_Equipment[ITEM_EQUIP]._item = NULL;

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
	/*for (int i = 0; i < ITEM_EQUIPMENT_SIZE; i++) {
		if (m_Equipment[i]._item != NULL) {
			if (m_Inventory->isEmpty()) {
				m_Inventory->setItem(m_Equipment[i]._item);
				_equipment[i]._item = NULL;
			}
		}
	}*/
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
			if (m_Equipment[i]._item->getWeaponType() == TYPE_WEAPON) {
				PLAYER->setEquipFlameWand(true);
			}
			else PLAYER->setEquipFlameWand(false);
		}
	}
}

Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}
