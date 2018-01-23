#pragma once
#include "player1.h"

class playerManager
{
public:
	playerManager();
	~playerManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

