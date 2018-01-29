#pragma once
#include "enemyBase.h"

#define DRAKESPEED 2.0f
#define DELAYTIME 50
#define HITCOUNT  10
#define DEADCOUNT 10

class minion3 : public enemyBase
{
private:
	bool _isHitPlay;

public:
	minion3();
	~minion3();


	HRESULT init(float x, float y);
	void update();
	void move();
	void draw();
};

