#pragma once
#include "scene.h"


class ShopScene : public scene
{
private:

	

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	ShopScene();
	~ShopScene();
};

