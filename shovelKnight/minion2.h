#pragma once
#include "enemyBase.h"

#define BLORBSPEED 1
#define DELAYTIME 70
#define HITCOUNT  10
#define DEADCOUNT 10

class minion2 : public enemyBase
{
private:
	int _jumpTime;


public:
	minion2();
	~minion2();

	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void move();
	void draw();

	void enemyInitSet();
	void enemyPattern(int _patternTypeNum);
};

