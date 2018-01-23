#pragma once

class gameObjectBase
{
public:
	gameObjectBase();
	~gameObjectBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

