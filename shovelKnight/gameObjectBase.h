#pragma once
#include "gameNode.h"

class gameObjectBase : public gameNode
{
protected :
	image* _image;
	RECT _rc;
	int _dur; //³»±¸µµ(HP°³³ä)
	float _x, _y;


public:
	gameObjectBase();
	~gameObjectBase();

	virtual HRESULT init(float x, float y, string imageKeyName, int dur);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void collisionReaction(enum target);
};

