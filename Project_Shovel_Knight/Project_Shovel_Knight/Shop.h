#pragma once

class Inventory;
class Item;

class Shop
{
private:

	RECT m_rc;
	Inventory* m_Inventory;
	vector<Item*> v_Item_List;

	image*	m_shopIMG;
	image*	m_Select;

	float m_fx, m_fy;
	bool ShopOn;
	RECT MoveRect;
	RECT ItemListRect;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void setInventoryLink(Inventory* link) { m_Inventory = link; }

	Shop();
	~Shop();
};

