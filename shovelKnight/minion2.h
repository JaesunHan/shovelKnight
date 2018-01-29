#pragma once
#include "enemyBase.h"

#define BLORBSPEED 1
#define DELAYTIME 70  //피격후 쿨타임
#define HITCOUNT  10  //피격상태 유지 카운트
#define DEADCOUNT 10  //데드상태 유지 카운트

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

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
};

