#pragma once
class gameCollision
{
public:
	gameCollision();
	~gameCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

