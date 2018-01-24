#pragma once
#include "menuBase.h"
class playerListMenu : public menuBase
{
	
public:
	HRESULT init();
	void update();
	void release();
	void render();
	void draw();


	playerListMenu();
	~playerListMenu();
};

