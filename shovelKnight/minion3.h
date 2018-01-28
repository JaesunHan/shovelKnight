#pragma once
#include "enemyBase.h"

#define DRAKESPEED 2.0f

class minion3 : public enemyBase
{
private:


public:
	minion3();
	~minion3();


	HRESULT init(float x, float y);
	void update();
	void move();
};

