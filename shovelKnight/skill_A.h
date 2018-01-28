#pragma once
#include "skillBase.h"

class skill_A : public skillBase
{
public:
	skill_A();
	~skill_A();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(SKILL_FIRE charType, float x, float y);
	virtual void reRect();
};

