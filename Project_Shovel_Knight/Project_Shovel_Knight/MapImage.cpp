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
	Stage_13 = IMAGEMANAGER->addImage("MainRunMap13", "image/RunAndGun_Map/Stage_13.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_14 = IMAGEMANAGER->addImage("MainRunMap14", "image/RunAndGun_Map/Stage_14.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_15 = IMAGEMANAGER->addImage("MainRunMap15", "image/RunAndGun_Map/Stage_15.bmp", 576, 208, true, RGB(255, 0, 255));
	Stage_16 = IMAGEMANAGER->addImage("MainRunMap16", "image/RunAndGun_Map/Stage_16.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_17 = IMAGEMANAGER->addImage("MainRunMap17", "image/RunAndGun_Map/Stage_17.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_18 = IMAGEMANAGER->addImage("MainRunMap18", "image/RunAndGun_Map/Stage_18.bmp", 800, 208, true, RGB(255, 0, 255));
	Stage_19 = IMAGEMANAGER->addImage("MainRunMap19", "image/RunAndGun_Map/Stage_19.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_20 = IMAGEMANAGER->addImage("MainRunMap20", "image/RunAndGun_Map/Stage_20.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_21 = IMAGEMANAGER->addImage("MainRunMap21", "image/RunAndGun_Map/Stage_21.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_22 = IMAGEMANAGER->addImage("MainRunMap22", "image/RunAndGun_Map/Stage_22.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_23 = IMAGEMANAGER->addImage("MainRunMap23", "image/RunAndGun_Map/Stage_24.bmp", 400, 208, true, RGB(255, 0, 255));
	Stage_24 = IMAGEMANAGER->addImage("MainRunMap24", "image/RunAndGun_Map/Stage_25.bmp", 400, 208, true, RGB(255, 0, 255));

	

	return S_OK;
}

MapImage::MapImage()
{
}


MapImage::~MapImage()
{
}
