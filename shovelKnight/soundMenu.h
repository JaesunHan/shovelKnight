#pragma once
#include "menuBase.h"
class soundMenu : public menuBase
{
public:


	

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);


	soundMenu();
	~soundMenu();
};

