#include "stdafx.h"
#include "Flame_Wand.h"


Flame_Wand::Flame_Wand()
{
	m_image = IMAGEMANAGER->addImage("Flame_Wand", "image/Item/Flame_Wand.bmp", 13, 13);
	m_Type = ITEM_EQUIP;
	m_WeaponType = TYPE_WEAPON;
	m_cost = 1000;
}


Flame_Wand::~Flame_Wand()
{
}
