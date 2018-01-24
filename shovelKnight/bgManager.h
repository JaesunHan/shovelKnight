#pragma once
class bgManager
{
public:
	bgManager();
	~bgManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

