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
};
