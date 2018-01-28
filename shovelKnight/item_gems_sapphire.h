#pragma once
#include "itemBase.h"
class item_gems_sapphire : public itemBase
{
public:
	item_gems_sapphire();
	~item_gems_sapphire();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

