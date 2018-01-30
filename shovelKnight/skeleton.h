#pragma once
#include "enemyBase.h"

#define SKELETONSPEED 2.0f
#define DELAYTIME 60  //피격후 쿨타임
#define HITCOUNT  10  //피격상태 유지 카운트
#define DEADCOUNT 20  //데드상태 유지 카운트

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

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
	virtual void attackCollisionRect();
};

