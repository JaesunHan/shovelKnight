#pragma once
#include "itemBase.h"
class item_gems_money : public itemBase
{
public:
	item_gems_money();
	~item_gems_money();

	virtual HRESULT init();
	virtual void release();
};

