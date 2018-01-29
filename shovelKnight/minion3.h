#pragma once
#include "enemyBase.h"

#define DRAKESPEED 2.0f
#define DELAYTIME 30  //피격후 쿨타임
#define HITCOUNT  10  //피격상태 유지 카운트
#define DEADCOUNT 10  //데드상태 유지 카운트


class minion3 : public enemyBase
{
private:
	bool _isHitPlay;

public:
	minion3();
	~minion3();


	HRESULT init(float x, float y);
	HRESULT init(float x, float y, int patternType);
	void update();
	void move();
	void draw();

	inline void enemyInitSet();
	inline void enemyPattern(int _patternTypeNum);
};

