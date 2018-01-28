#pragma once
#include "itemBase.h"

class item_apple : public itemBase
{
public:
	item_apple();
	~item_apple();

	virtual HRESULT init();
	virtual void release();
};

