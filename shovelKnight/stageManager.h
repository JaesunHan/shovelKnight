#pragma once
#include "gameNode.h"

class stageManager : public gameNode
{
public:

	HRESULT init();
	void release();
	void update();
	void render();

	stageManager();
	~stageManager();
};

