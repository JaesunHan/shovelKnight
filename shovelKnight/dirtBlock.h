#pragma once
#include "gameObjectBase.h"

class dirtBlock : public gameObjectBase
{
public:
	dirtBlock();
	~dirtBlock();

	virtual HRESULT init()	= 0;
	virtual void release()	= 0;
	virtual void update()	= 0;
	virtual void render()	= 0;
};

