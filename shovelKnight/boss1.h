#pragma once
#include "enemyBase.h"

#define DRAGONSPEED 2

class boss1 : public enemyBase
{
private:


public:
	boss1();
	~boss1();

	HRESULT init(float x, float y);
	void update();
	void move();
};

