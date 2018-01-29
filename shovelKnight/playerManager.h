#pragma once
#include "player1.h"

class stageManager;
class gameCollision;
class skillManager;

class playerManager
{
private : 
	playerBase* _p1;
	stageManager* _SM;
	gameCollision* _GC;
	skillManager* _skillM;
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
	inline void setSkillUnlockLv(int skillLv) { _p1->setSkillUnlockLv(skillLv); }
	inline void setStageManagerMemoryAddressLink(stageManager* sm) { _SM = sm; }
	inline void setGameCollisinMemoryAddressLink(gameCollision* gc) { _GC = gc; }
	inline void setSkillManagerMemoryAddressLink(skillManager* skillm) { _skillM = skillm; }
	inline void setPlayerPause(bool pause) { _p1->setPause(pause); }
	//IDLE = 0, MOVE = 1, ATTACK = 2, JUMP = 3, ROOTING = 4, DAMAGED = 5, DIE = 6
	inline int getPlayerAction() { return _p1->getPlayerAction(); }
	inline void setDamagePlayer() { _p1->setDamagePlayer(); }
	inline void setPlayerReaction() { _p1->setAttackReaction(); }
	inline RECT getPlayerRC() { return _p1->getPlayerRC(); }
	inline RECT getAttackRC() { return _p1->getAttackRC(); }


};

