#pragma once
#include "gameNode.h"
#include "minion1.h"

#include <vector>


class enemyManager 
{
private:
	typedef vector<minion1*>			vMinion1;
	typedef vector<minion1*>::iterator	viMinion1;

private:
	vMinion1	_vBeeto;
	viMinion1   _viBeeto;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//========================================= Start 미니언 셋팅 ========================================
	//--------------------------------- beeto
	void setMinionBeeto(void);
	void removeMinionBeeto(int arrNum);

	//========================================== End 미니언 셋팅 =========================================


	//==================================== Start 접근자 설정자 작성하기===================================
	//------------------------------------------------------------------------ beeto
	vector<minion1*> getVBeeto() { return _vBeeto; }
	vector<minion1*>::iterator getVIBeeto() { return _viBeeto; }

	//===================================== End 접근자 설정자 작성하기====================================

};

