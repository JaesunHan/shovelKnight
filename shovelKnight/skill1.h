#pragma once
#include "skillBase.h"
class skill1 :
	public skillBase
{
public:
	skill1();
	~skill1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

