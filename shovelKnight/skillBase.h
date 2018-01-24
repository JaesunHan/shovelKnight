#pragma once
#include "gameNode.h"

class skillBase
{
public:
	skillBase();
	~skillBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

