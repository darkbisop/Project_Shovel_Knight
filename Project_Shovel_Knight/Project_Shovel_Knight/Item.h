#pragma once

struct Option
{
	int Cost;
};

enum Item_Type
{
	ITEM_EQUIP
};

enum weponType
{
	TYPE_WEAPON, TYPE_ACCESSORY
};

typedef vector<Option> vOption;
typedef vector<Option>::iterator vIOpntion;

class Item
{
protected:

	image*		m_image;
	Item_Type	m_Type;
	weponType	m_WeaponType;
	int			m_cost;

public:

	image* getImage() { return m_image; }
	Item_Type getType() { return m_Type; }
	weponType getWeaponType() { return m_WeaponType; }
	int getCost() { return m_cost; }

	Item();
	~Item();
};

