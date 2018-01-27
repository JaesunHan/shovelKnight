#pragma once
#include "enemyBase.h"

#define SKELETONSPEED 2.0f

class skeleton : public enemyBase
{
private:


public:
	skeleton();
	~skeleton();

	HRESULT init(float x, float y);
	void update();
	void move();
};

