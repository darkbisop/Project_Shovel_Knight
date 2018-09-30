#include "stdafx.h"
#include "MapImage.h"


HRESULT MapImage::init()
{
	Stage_1 = IMAGEMANAGER->addImage("MainRunMap", "image/RunAndGun_Map/Stage_1.bmp", 1600, 208, true, RGB(255, 0, 255));
	Stage_2 = IMAGEMANAGER->addImage("MainRunMap2", "image/RunAndGun_Map/Stage_2.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_3 = IMAGEMANAGER->addImage("MainRunMap3", "image/RunAndGun_Map/Stage_3.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_4 = IMAGEMANAGER->addImage("MainRunMap4", "image/RunAndGun_Map/Stage_4.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_5 = IMAGEMANAGER->addImage("MainRunMap5", "image/RunAndGun_Map/Stage_5.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_6 = IMAGEMANAGER->addImage("MainRunMap6", "image/RunAndGun_Map/Stage_6.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_7 = IMAGEMANAGER->addImage("MainRunMap7", "image/RunAndGun_Map/Stage_7.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_8 = IMAGEMANAGER->addImage("MainRunMap8", "image/RunAndGun_Map/Stage_8.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_9 = IMAGEMANAGER->addImage("MainRunMap9", "image/RunAndGun_Map/Stage_9.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_10 = IMAGEMANAGER->addImage("MainRunMap10", "image/RunAndGun_Map/Stage_10.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_11 = IMAGEMANAGER->addImage("MainRunMap11", "image/RunAndGun_Map/Stage_11.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_12 = IMAGEMANAGER->addImage("MainRunMap12", "image/RunAndGun_Map/Stage_12.bmp", 400, 208, true, RGB(255, 0, 255));

	return S_OK;
}

MapImage::MapImage()
{
}


MapImage::~MapImage()
{
}
