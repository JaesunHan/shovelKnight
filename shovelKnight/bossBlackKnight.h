#pragma once
#include "enemyBase.h"

#define BLACKKNIGHTSPEED 2
#define DELAYTIME 70  //피격후 쿨타임
#define HITCOUNT  10  //피격상태 유지 카운트
#define DEADCOUNT 50  //데드상태 유지 카운트

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

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
};

