#pragma once
#include "enemyBase.h"

#define BEETOSPEED 1
#define DELAYTIME 70
#define HITCOUNT  10
#define DEADCOUNT 20


class minion1 : public enemyBase
{
private:



public:
	minion1();
	~minion1();

	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void move();

	void enemyInitSet();
	void enemyPattern(int _patternTypeNum);
};

