#pragma once
#include "enemyBase.h"

#define BEETOSPEED 1


class minion1 : public enemyBase
{
private:



public:
	minion1();
	~minion1();

	HRESULT init(float x, float y);
	void update();
	void move();
};

