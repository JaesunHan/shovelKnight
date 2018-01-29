#pragma once
#include "enemyBase.h"

#define SKELETONSPEED 2.0f

class skeleton : public enemyBase
{
private:
	bool _isHit;		//hit 판정후 상태값 변경을 위한 변수
	bool _isAttack;     //attack 상태

public:
	skeleton();
	~skeleton();

	HRESULT init(float x, float y);
	void update();
	void move();
};

