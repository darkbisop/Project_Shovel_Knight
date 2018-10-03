#pragma once

#define INVENTORY_X 6
#define INVENTORY_Y 2

class Item;
class Equipment;

struct Slot
{
	Item* m_pItem;
	RECT  _rect;
};

class Inventory
{
private:

	image * m_InventoryImg;
	image*	m_SelectImg;

	Equipment* m_pEquipment;
	RECT	m_rc;
	RECT	Select_Rect;
	int		Money;
	int		m_InvenY;
	Slot	m_Inventory[2][6];

	float	m_fx, m_fy;

	bool	invenOn;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void SetEquipmentLink(Equipment* link) { m_pEquipment = link; }

	void buyItem(Item* item);
	void sellItem(int x, int y);
	void setItem(Item* item);
	bool isEmpty();

	void setInvenOn(bool a) { invenOn = a; }

	Inventory();
	~Inventory();
};

