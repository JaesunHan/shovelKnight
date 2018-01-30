#pragma once
#include "skillBase.h"

class skill_dirtBlockFx : public skillBase
{
public:
	skill_dirtBlockFx();
	~skill_dirtBlockFx();

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void fire(SKILL_FIRE charType, float x, float y);
};