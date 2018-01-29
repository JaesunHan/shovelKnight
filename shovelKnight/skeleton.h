#pragma once
#include "enemyBase.h"

#define SKELETONSPEED 2.0f
#define DELAYTIME 60
#define HITCOUNT  10
#define DEADCOUNT 20

class skeleton : public enemyBase
{
private:


public:
	skeleton();
	~skeleton();

	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void move();
	void draw();

	void enemyInitSet();
	void enemyPattern(int _patternTypeNum);
};

