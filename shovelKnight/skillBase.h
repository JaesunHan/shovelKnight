#pragma once
#include "gameNode.h"

class skillBase
{
	float _x;
	float _y;
	RECT _rc;
	image* _img;
	int _imgWidth;
	int _imgHeight;
	

public:
	skillBase();
	~skillBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float x, float y);
	virtual void reRect();
};

