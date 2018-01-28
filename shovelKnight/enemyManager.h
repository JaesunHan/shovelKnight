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
	typedef vector<enemyBase*>				vEnemy1;
	typedef vector<enemyBase*>::iterator	viEnemy1;

private:
	vEnemy1		_vEnemy;
	viEnemy1	_viEnemy;

	bool _enemyIsOn[3];

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//미니언 생성&소멸 접근자
	void setStage1EnemyOn(bool isOn) { _enemyIsOn[0] = isOn; }
	void setStage2EnemyOn(bool isOn) { _enemyIsOn[1] = isOn; }
	void setStage3EnemyOn(bool isOn) { _enemyIsOn[2] = isOn; }

	//========================================= Start 미니언 셋팅 ========================================

	void setEnemy(ENEMYTYPE enemyType, float enemyX, float enemyY);
	void removeEnemy(int arrNum);

	//========================================== End 미니언 셋팅 =========================================


	//==================================== Start 접근자 설정자 작성하기===================================

	vector<enemyBase*> getVEnemy() { return _vEnemy; }
	vector<enemyBase*>::iterator getVIEnemy() { return _viEnemy; }

	//===================================== End 접근자 설정자 작성하기====================================

};

