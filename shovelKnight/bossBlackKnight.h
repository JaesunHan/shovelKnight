#pragma once
#include "enemyBase.h"

class bossBlackKnight : public enemyBase
{


public:
	bossBlackKnight();
	~bossBlackKnight();

	HRESULT init(float x, float y);
	void update();
	void move();
	void draw();

};

