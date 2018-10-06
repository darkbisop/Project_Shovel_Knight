#pragma once
class obejectBasicInfo
{
protected:

	RECT	_rc;
	int		_Count;
	float	_x, _y;
	float	_angle;
	float	_gravity;
	bool	_isAlive;

public:

	HRESULT init(float x, float y);
	void release();
	void update();
	void render(HDC hdc);

	obejectBasicInfo();
	~obejectBasicInfo();
};

