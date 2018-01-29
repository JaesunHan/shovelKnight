#pragma once
#include "skillBase.h"

class skill_Bubble : public skillBase
{
private:
	float _startX = 0;

public:
	skill_Bubble();
	~skill_Bubble();

	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void fire(SKILL_FIRE charType, float x, float y);

	static void* isOut(void* obj);

	void asd() {};
};