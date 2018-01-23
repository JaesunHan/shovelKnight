#pragma once
#include "enemy1.h"

class enemyManager
{
public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

