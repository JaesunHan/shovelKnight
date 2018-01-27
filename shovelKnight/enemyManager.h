#pragma once
#include "gameNode.h"
#include "minion1.h"
#include "minion2.h"
#include "minion3.h"
#include "boss1.h"

#include <vector>


class enemyManager 
{
private:
	typedef vector<minion1*>			vMinion1;
	typedef vector<minion1*>::iterator	viMinion1;

	typedef vector<minion2*>            vMinion2;
	typedef vector<minion2*>::iterator	viMinion2;

	typedef vector<minion3*>            vMinion3;
	typedef vector<minion3*>::iterator	viMinion3;

	typedef vector<boss1*>              vBoss1;
	typedef vector<boss1*>::iterator	viBoss1;

private:
	vMinion1	_vBeeto;
	viMinion1   _viBeeto;

	vMinion2	_vBlorb;
	viMinion2   _viBlorb;

	vMinion3	_vDrake;
	viMinion3   _viDrake;

	vBoss1		_vDragon;
	viBoss1		_viDragon;

	bool _enemyIsOn;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//미니언 생성&소멸 접근자
	void setEnemyIsOn(bool isOn) { _enemyIsOn = isOn; }

	//========================================= Start 미니언 셋팅 ========================================
	//--------------------------------- beeto
	void setMinionBeeto(void);
	void removeMinionBeeto(int arrNum);

	//--------------------------------- blorb
	void setMinionBlorb(void);
	void removeMinionBlorb(int arrNum);

	//--------------------------------- drake
	void setMinionDrake(void);
	void removeMinionDrake(int arrNum);

	//--------------------------------- dragon
	void setBossDragon(void);
	void removeBossDragon(int arrNum);

	//========================================== End 미니언 셋팅 =========================================


	//==================================== Start 접근자 설정자 작성하기===================================
	//------------------------------------------------------------------------ beeto
	vector<minion1*> getVBeeto() { return _vBeeto; }
	vector<minion1*>::iterator getVIBeeto() { return _viBeeto; }

	//------------------------------------------------------------------------ blorb
	vector<minion2*> getVBlorb() { return _vBlorb; }
	vector<minion2*>::iterator getVIBlorb() { return _viBlorb; }

	//------------------------------------------------------------------------ drake
	vector<minion3*> getVDrake() { return _vDrake; }
	vector<minion3*>::iterator getVIDrake() { return _viDrake; }

	//===================================== End 접근자 설정자 작성하기====================================

};

