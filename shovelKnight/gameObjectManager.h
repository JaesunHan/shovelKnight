#pragma once
#include "gameObject1.h"
#include <vector>


class gameObjectManager
{
private :
	typedef vector<gameObjectBase>;


public:
	gameObjectManager();
	~gameObjectManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

