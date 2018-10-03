#pragma once
#include "Item.h"

class Inventory;

#define ITEM_EQUIPMENT_SIZE 1

struct Item_Slot
{
	Item_Type _type;
	RECT _rect;
	Item* _item;
};

class Equipment
{
private:

	RECT EquipRect;
	Inventory* m_Inventory;
	Item_Slot m_Equipment[ITEM_EQUIPMENT_SIZE];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void setInventoryLink(Inventory* link) { m_Inventory = link; }
	Item* setEquipment(Item* item);
	void setItemEffect();

	Equipment();
	~Equipment();
};

