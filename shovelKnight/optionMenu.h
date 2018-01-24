#pragma once
#include "menuBase.h"
class optionMenu : public menuBase
{
public:
	HRESULT init();
	void update();
	void release();
	void render();
	void draw(HDC hdc);


	optionMenu();
	~optionMenu();
};

