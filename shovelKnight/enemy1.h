#pragma once
#include "enemyBase.h"

class enemy1 : public enemyBase
{
public:
	enemy1();
	~enemy1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

