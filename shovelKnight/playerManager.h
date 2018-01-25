#pragma once
#include "player1.h"

class playerManager
{
private : 
	playerBase* _p1;


public:
	playerManager();
	~playerManager();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return _p1->getX(); }
	void setX(float x) { _p1->setX(x); }
	float getY() { return _p1->getY(); }
	void setY(float y) { _p1->setY(y); }
	int	getMaxHP() { return _p1->getMaxHP(); }
	void setMaxHP(int increaseHP) { _p1->setMaxHP(increaseHP); }
	int	getMaxMP() { return _p1->getMaxMP(); }
	void setMaxMP(int increaseMP) { _p1->setMaxMP(increaseMP); }
	int	getMoney() { return _p1->getMoney(); }
	void setMoney(int increaseMoney) { _p1->setMoney(increaseMoney); }


	RECT getPlayerRc() { return _p1->getPlayerRc(); }
	void setPlayerRc(RECT rc) { _p1->setPlayerRc(rc); }
	COLLISION_PLAYER getCollisionPlayer() { return _p1->getCollisionPlayer(); }


};

