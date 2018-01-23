#pragma once
class bgBase
{
public:
	bgBase();
	~bgBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

