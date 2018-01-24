#pragma once
#include "skillBase.h"

class skill_Bubble : public skillBase
{
public:
	skill_Bubble();
	~skill_Bubble();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

