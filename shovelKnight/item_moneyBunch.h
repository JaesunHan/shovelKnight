#pragma once
#include "itemBase.h"
class item_moneyBunch : public itemBase
{
public:
	item_moneyBunch();
	~item_moneyBunch();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
};

