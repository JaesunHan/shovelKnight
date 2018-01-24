#pragma once
#include "gameNode.h"

class gameObjectBase
{
protected:
	float _x, _y;
	int _dur;
	image* _image;
	RECT _rc;

public:
	gameObjectBase();
	~gameObjectBase();

	virtual HRESULT init(float x, float y, string imageKeyName, int dur);
	virtual void release();
	virtual void update();
	virtual void render();
};

