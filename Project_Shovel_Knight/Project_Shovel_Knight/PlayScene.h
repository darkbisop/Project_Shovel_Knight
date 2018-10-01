#pragma once
#include "scene.h"

class PlayScene : public scene
{

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	PlayScene();
	~PlayScene();
};

