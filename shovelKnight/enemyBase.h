#pragma once

class enemyBase
{
public:
	enemyBase();
	~enemyBase();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

