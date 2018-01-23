#pragma once
class npcBase
{
public:
	npcBase();
	~npcBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

