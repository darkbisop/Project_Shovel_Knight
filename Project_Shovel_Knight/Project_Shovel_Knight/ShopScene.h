#pragma once
#include "scene.h"
#include "Shop.h"


class ShopScene : public scene
{
private:

	image* bg;
	Shop*		m_Shop;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	ShopScene();
	~ShopScene();
};

