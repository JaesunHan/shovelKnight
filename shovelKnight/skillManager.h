#pragma once
#include "skill1.h"

class skillManager
{
public:
	skillManager();
	~skillManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

