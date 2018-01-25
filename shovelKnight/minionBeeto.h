#pragma once
#include "enemyBase.h"


class minionBeeto : public enemyBase
{
private:



public:
	minionBeeto();
	~minionBeeto();

	HRESULT init(string imgKeyString, char* imgFileName, float x, float y, int totalWidth, int totalHeight, int frameX, int frameY);
	void move();


};

