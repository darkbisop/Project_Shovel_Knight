#include "stdafx.h"
#include "TempItem.h"


TempItem::TempItem()
{
	m_image = IMAGEMANAGER->addImage("Invi", "image/Item/Invi.bmp", 13, 13);
	m_Type = ITEM_EQUIP;
	m_cost = 1000;
}


TempItem::~TempItem()
{
}
