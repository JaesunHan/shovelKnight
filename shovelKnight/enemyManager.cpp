#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}
enemyManager::~enemyManager()
{
}


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{

}

void enemyManager::render()
{

}



//============================================== 미니언 셋팅
void enemyManager::setMinionBeeto(void)
{
	minionBeeto* beeto;
	beeto = new minionBeeto;

	beeto->init(100, 100);

}

void enemyManager::removeMinionBeeto(int arrNum)
{

}