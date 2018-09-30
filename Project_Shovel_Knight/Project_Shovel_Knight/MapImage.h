#pragma once
class MapImage
{
private:

	image*	Stage_1;
	image*	Stage_2;
	image*	Stage_3;
	image*	Stage_4;
	image*	Stage_5;
	image*	Stage_6;
	image*	Stage_7;
	image*	Stage_8;
	image*	Stage_9;

public:
	
	HRESULT init();

	MapImage();
	~MapImage();
};

