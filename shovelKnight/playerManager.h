#pragma once
#include "player1.h"

class stageManager;

class playerManager
{
private : 
	playerBase* _p1;
	stageManager* _SM;
public:
	playerManager();
	~playerManager();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	inline float getX() { return _p1->getPlayerX(); }
	inline void setX(float x) { _p1->setPlayerX(x); }
	inline float getY() { return _p1->getPlayerY(); }
	inline void setY(float y) { _p1->setPlayerY(y); }
	inline int	getMaxHP() { return _p1->getPlayerMaxHP(); }
	inline void setMaxHP(int increaseHP) { _p1->setPlayerMaxHP(increaseHP); }
	inline int	getMaxMP() { return _p1->getPlayerMaxMP(); }
	inline void setMaxMP(int increaseMP) { _p1->setPlayerMaxMP(increaseMP); }
	inline int	getMoney() { return _p1->getMoney(); }
	inline void setMoney(int increaseMoney) { _p1->setMoney(increaseMoney); }
	inline int getSkillUnlockLv() { return _p1->getSkillUnlockLv(); }
	inline void setSkillUnlockLv(int increaseLv) { _p1->setSkillUnlockLv(increaseLv); }
	inline void setStageManagerMemoryAddressLink(stageManager* sm) { _SM = sm; }
	inline void setPlayerPause(bool pause) { _p1->setPause(pause); }

	RECT getPlayerRc() { return _p1->getPlayerRc(); }


};

