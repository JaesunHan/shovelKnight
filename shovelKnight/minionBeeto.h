#pragma once
#include "enemyBase.h"


class minionBeeto : public enemyBase
{
private:



public:
	minionBeeto();
	~minionBeeto();

	HRESULT init(float x, float y);
	void move();


};

