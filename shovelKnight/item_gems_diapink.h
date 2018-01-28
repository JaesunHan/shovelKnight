#pragma once
#include "itemBase.h"

class item_gems_diapink : public itemBase
{
public:
	item_gems_diapink();
	~item_gems_diapink();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
};

