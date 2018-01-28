#pragma once
#include "menuBase.h"
class createCharacterMenu : public menuBase
{
public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void draw(HDC hdc);

	createCharacterMenu();
	~createCharacterMenu();
};

