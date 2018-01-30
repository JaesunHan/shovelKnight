#pragma once
#include "skillBase.h"

class skill_darkKnight_fireBall : public skillBase
{
public:
	skill_darkKnight_fireBall();
	~skill_darkKnight_fireBall();

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void fire(SKILL_FIRE charType, float x, float y);
};