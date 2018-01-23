#pragma once
#include "itemBase.h"
class item1 :
	public itemBase
{
public:
	item1();
	~item1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

