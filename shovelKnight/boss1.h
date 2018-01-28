#pragma once
#include "enemyBase.h"

#define DRAGONSPEED 1

class boss1 : public enemyBase
{
private:
	int _movePatternCount;

public:
	boss1();
	~boss1();

	HRESULT init(float x, float y);
	void update();
	void move();
};

