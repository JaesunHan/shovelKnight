#pragma once
#include "bgBase.h"

class bg1 : public bgBase
{
public:
	bg1();
	~bg1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

