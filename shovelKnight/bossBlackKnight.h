#pragma once
#include "enemyBase.h"

#define BEETOSPEED 1
#define DELAYTIME 70
#define HITCOUNT  10
#define DEADCOUNT 50

class bossBlackKnight : public enemyBase
{


public:
	bossBlackKnight();
	~bossBlackKnight();

	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void move();
	void draw();

	void enemyInitSet();
	void enemyPattern(int _patternTypeNum);
};

