#pragma once
#include "enemyBase.h"

#define BLACKKNIGHTSPEED 2
#define DELAYTIME 50  //피격후 쿨타임
#define HITCOUNT  25  //피격상태 유지 카운트
#define DEADCOUNT 30  //데드상태 유지 카운트

class bossBlackKnight : public enemyBase
{
private:


public:
	bossBlackKnight();
	~bossBlackKnight();

	virtual HRESULT init(float x, float y);
	virtual HRESULT init(float x, float y, int patternType);
	virtual void update();
	virtual void move();
	virtual void draw();

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
};

