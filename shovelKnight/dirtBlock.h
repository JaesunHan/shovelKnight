#pragma once
#include "gameObjectBase.h"

class dirtBlock : public gameObjectBase
{
public:
	dirtBlock();
	~dirtBlock();

	HRESULT init(float x,float y);
	void update();
	void render();
};

