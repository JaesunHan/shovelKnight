#pragma once
#include "skillBase.h"


class skill_fireBall : public skillBase
{
private:

public:
	skill_fireBall();
	~skill_fireBall();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void startLoopFire(void* obj);
	static void outFire(void* obj);
};

