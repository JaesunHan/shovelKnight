#pragma once
#include "skillBase.h"

class skill_enemyDeadFx : public skillBase
{
public:
	skill_enemyDeadFx();
	~skill_enemyDeadFx();

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void fire(SKILL_FIRE charType, float x, float y);

	static void* isOut(void* obj);
};