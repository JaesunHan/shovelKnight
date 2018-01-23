#pragma once
#include "playerBase.h"
class player1 : public playerBase
{
public:
	player1();
	~player1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

