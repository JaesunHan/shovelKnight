#pragma once
#include "gameObject1.h"

class gameObjectManager
{
public:
	gameObjectManager();
	~gameObjectManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

