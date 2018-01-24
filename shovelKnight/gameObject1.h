#pragma once
#include "gameObjectBase.h"
class gameObject1 : public gameObjectBase
{
public:
	gameObject1();
	~gameObject1();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

