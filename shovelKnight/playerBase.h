#pragma once
class playerBase
{
public:
	playerBase();
	~playerBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

