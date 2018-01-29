#pragma once
#include "gameObjectBase.h"

class checkPoint : public gameObjectBase
{
public:
	checkPoint();
	~checkPoint();

	HRESULT init(float x, float y);
	void update();
	void render();
};

