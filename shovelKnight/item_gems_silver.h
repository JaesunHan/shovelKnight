#pragma once
#include "itemBase.h"

class item_gems_silver : public itemBase
{
public:
	item_gems_silver();
	~item_gems_silver();

	virtual HRESULT init();
	virtual void release();
};

