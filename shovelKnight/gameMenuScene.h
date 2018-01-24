#pragma once
#include "gameNode.h"

class gameMenuScene : public gameNode
{
private:
	

public:

	HRESULT init();
	void update();
	void release();
	void render();
	void draw();
	


	gameMenuScene();
	~gameMenuScene();
};

