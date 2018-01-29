#pragma once
#include "enemyBase.h"

#define DRAGONSPEED 1
#define DRAGONHEADRECTX	 37.5
#define DRAGONHEADRECTY	 32
#define DRAGONTRUNKRECTX 25
#define DRAGONTRUNKRECTY 14.5
#define DELAYTIME	50
#define HITCOUNT	10
#define DEADCOUNT	30

class boss1 : public enemyBase
{
private:
	int _movePatternCount;


	float _headX, _headY;
	float _trunkX, _trunkY;

public:
	boss1();
	~boss1();

	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void render();
	void move();
	void draw();

	void enemyInitSet();
	void enemyPattern(int _patternTypeNum);
};

