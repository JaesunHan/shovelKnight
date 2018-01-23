#pragma once
class itemBase
{
public:
	itemBase();
	~itemBase();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

