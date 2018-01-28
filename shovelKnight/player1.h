#pragma once
#include "playerBase.h"
class player1 : public playerBase
{
private:
public:
	player1();
	~player1();

	HRESULT init();
	void release();
	void update();
	void render();

	void control2();
	void attack();
};

