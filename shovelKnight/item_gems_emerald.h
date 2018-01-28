#pragma once
#include "itemBase.h"
class item_gems_emerald : public itemBase
{
public:
	item_gems_emerald();
	~item_gems_emerald();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

