#include "stdafx.h"
#include "dirtBlock.h"


HRESULT dirtBlock::init(float x, float y)
{
	m_Img = IMAGEMANAGER->addImage("dirtBlock", "image/Object/dirtBlock.bmp", 32, 32, true, RGB(255, 0, 255));
	m_Sprite = IMAGEMANAGER->addImage("dirtBlockSprite", "image/Object/dirtBlockSprite.bmp", 135, 38, 3, 1, true, RGB(255, 0, 255));
	m_Gems = IMAGEMANAGER->addImage("Gem_4", "image/Object/Gem_4.bmp", 13, 9, true, RGB(255, 0, 255));
	
	m_fX = x;
	m_fY = y;
	m_angle = _angle;
	m_gravity = _gravity;
	_isAlive = true;
	m_crash = false;

	RanD = 0;
	RandGems = 0;
	
	return S_OK;
}

void dirtBlock::release()
{
}

void dirtBlock::update()
{
	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		v_Iter->gravity += 0.1f;
		if (v_Iter->gravity > 0.1f) {
			v_Iter->x += cosf(v_Iter->angle) * v_Iter->speed;
			v_Iter->y -= sinf(v_Iter->angle) * v_Iter->speed - v_Iter->gravity;
			v_Iter->isAlive = true;
			v_Iter->rc = RectMake(v_Iter->x, v_Iter->y, 5, 5);
		}
	}

	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		RECT rc;
		for (int i = 0; i < MAPMANAGER->getMapVectorRcSize(); i++) {
			if (IntersectRect(&rc, &v_Iter->rc, &MAPMANAGER->getMapVectorRc(i))) {
				v_Iter->gravity = 0;
				v_Iter->y = MAPMANAGER->getMapVectorRc(i).top - 7;
			}
		}
	}

	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end();) {
		RECT rc;
		if (IntersectRect(&rc, &v_Iter->rc, &PLAYER->getPlayerRect())) {
			SOUNDMANAGER->play("º¸¼®µæ", 0.5f);
			v_Iter->isAlive = false;
			v_Iter = v_VecJewel.erase(v_Iter);
		}

		else v_Iter++;
	}

	animation();

	if (_isAlive) _rc = RectMake(m_fX, m_fY, 32, 32);
}

void dirtBlock::render(HDC hdc)
{
	if (_isAlive) {
		//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
		m_Img->render(hdc, _rc.left, _rc.top);
		
	}

	if (m_crash) m_Sprite->frameRender(hdc, _rc.left - 5, _rc.top - 10, CurrFrame, 0);

	for (v_Iter = v_VecJewel.begin(); v_Iter != v_VecJewel.end(); v_Iter++) {
		if (v_Iter->isAlive) {
			//Rectangle(hdc, v_Iter->rc.left, v_Iter->rc.top, v_Iter->rc.right, v_Iter->rc.bottom);
			m_Gems->render(hdc, v_Iter->x - 6, v_Iter->y - 1);
		}
	}
}

void dirtBlock::animation()
{
	if (m_crash == true) {
		_isAlive = false;
		m_FrameCount++;
		if (m_FrameCount % 7 == 0) {
			CurrFrame++;
			m_Sprite->setFrameX(CurrFrame);

			if (CurrFrame > m_Sprite->getMaxFrameX()) {
				CurrFrame = 0;
				m_crash = false;
				_rc = RectMake(-1, -1, -1, -1);
			}
		}
	}
}

void dirtBlock::DigOut()
{
	if (_isAlive == true) {
		RanD = RANDOM->getFromIntTo(1, 10);

		if (RanD == 1) {
			m_Drop.x = m_fX + 17;
			m_Drop.y = m_fY + 2;
			m_Drop.gravity = 0;
			m_Drop.angle = 90 * 3.14 / 180;
			m_Drop.speed = 3.0f;
			v_VecJewel.push_back(m_Drop);
		}
	}
}

dirtBlock::dirtBlock()
{
}


dirtBlock::~dirtBlock()
{
}
