#pragma once
#include "gameNode.h"
#include "minionBeeto.h"

#include <vector>


class enemyManager : public gameNode
{
private:
	typedef vector<minionBeeto*>			vMinion1;
	typedef vector<minionBeeto*>::iterator	viMinion1;

private:
	vMinion1 _vBeeto;


public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//============================ 미니언 셋팅
	//beeto
	void setMinionBeeto(void);
	void removeMinionBeeto(int arrNum);
};

