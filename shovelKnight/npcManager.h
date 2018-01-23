#pragma once
class npcManager
{
public:
	npcManager();
	~npcManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

