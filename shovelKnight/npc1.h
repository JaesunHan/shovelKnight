#pragma once
class npc1
{
public:
	npc1();
	~npc1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

