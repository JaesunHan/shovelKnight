#pragma once
#include "enemyBase.h"

#define BEETOSPEED 1
#define DELAYTIME 70   //피격후 쿨타임
#define HITCOUNT  10   //피격상태 유지 카운트
#define DEADCOUNT 20   //데드상태 유지 카운트


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

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
};

