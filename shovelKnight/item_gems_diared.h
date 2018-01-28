#pragma once
#include "itemBase.h"

class item_gems_diared : public itemBase
{
public:
	item_gems_diared();
	~item_gems_diared();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

