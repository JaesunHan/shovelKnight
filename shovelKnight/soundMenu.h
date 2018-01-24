#pragma once
#include "menuBase.h"
class soundMenu
{
public:
	HRESULT init();
	void update();
	void release();
	void render();
	void draw(HDC hdc);


	soundMenu();
	~soundMenu();
};

