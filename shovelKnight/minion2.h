#pragma once
#include "enemyBase.h"

#define BLORBSPEED 1

class minion2 : public enemyBase
{
private:
	int _jumpTime;


public:
	minion2();
	~minion2();

	HRESULT init(float x, float y);
	void update();
	void move();
	void draw();
};

