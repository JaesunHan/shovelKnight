#pragma once

class gameObjectBase
{
public:
	gameObjectBase();
	~gameObjectBase();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

