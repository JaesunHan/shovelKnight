#pragma once
#include "skillBase.h"

class skill_fireBall : public skillBase
{
public:
	skill_fireBall();
	~skill_fireBall();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(SKILL_FIRE charType, float x, float y);

	static void* goLoop(void* obj);
	static void* isOut(void* obj);
};

