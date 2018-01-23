#pragma once
class bgManager
{
public:
	bgManager();
	~bgManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

