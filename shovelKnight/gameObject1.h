#pragma once
#include "gameObjectBase.h"
class gameObject1 : public gameObjectBase
{
public:
	gameObject1();
	~gameObject1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

