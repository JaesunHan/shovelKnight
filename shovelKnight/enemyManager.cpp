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
	for (int i = 0; i < 3; ++i)
	{
		_enemyIsOn[i] = true;
	}

	//==================================== 적 생성
	//stage1
	if (_enemyIsOn[0])
	{
		setEnemy(ENEMY_BEETO, 200, 70);
		setEnemy(ENEMY_BLORB, 300, 200);
		setEnemy(ELEMY_DRAKE, 400, 150);
		setEnemy(ENEMY_DRAGON, 400, 200);
		setEnemy(ENEMY_SKELETON, 200, 150);
	}
	//====================================

	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	//============================================================================ 적 move start
	//-------------------------------------------------------------- 미니언 beeto
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{

		(*_viEnemy)->update();
	
	}

	//데드 TEST
	//for (int i = 0; i < _vEnemy.size(); i++)
	//{
	//	if (KEYMANAGER->isOnceKeyDown('1'))
	//	{
	//		if (_vEnemy[i]->getStatus() == ENEMY_LEFT_MOVE)
	//		{
	//			_vEnemy[i]->setStatus(ENEMY_LEFT_DEAD);
	//		}
	//		else if (_vEnemy[i]->getStatus() == ENEMY_RIGHT_MOVE)
	//		{
	//			_vEnemy[i]->setStatus(ENEMY_RIGHT_DEAD);
	//		}
	//	}
	//	//죽었으면 벡터에서 지우기
	//	if (_vEnemy[i]->getIsDeadVanish() == true)
	//	{
	//		removeEnemy(i);
	//	}
	//}
	//화면밖으로 사라지면 제거
	//for (int i = 0; i < _vDragon.size(); i++)
	//{
	//	if (_vDragon[i]->getRect().right < 0)
	//		removeBossDragon(i);
	//}
	//-------------------------------------------------------------- 
	//============================================================================ 적 move end
}

void enemyManager::render()
{
	//============================================================================ 적 render start

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{

		(*_viEnemy)->render();

	}

	//============================================================================ 적 render end
}



//======================================================================================== 에너미 셋팅 start
//                          에네미 종류          X좌표         Y좌표        
void enemyManager::setEnemy(ENEMYTYPE enemyType, float enemyX, float enemyY)
{
	enemyBase* minion;

	switch (enemyType)
	{
		case ENEMY_BEETO:

			minion = new minion1;
			minion->init(enemyX, enemyY);

		break;
		case ENEMY_BLORB:

			minion = new minion2;
			minion->init(enemyX, enemyY);
		
		break;
		case ELEMY_DRAKE:

			minion = new minion3;
			minion->init(enemyX, enemyY);

		break;
		case ENEMY_SKELETON:

			minion = new skeleton;
			minion->init(enemyX, enemyY);

		break;
		case ENEMY_DRAGON:

			minion = new boss1;
			minion->init(enemyX, enemyY);

		break;
		case ENEMY_BLACKKNIGHT:

			//minion = new boss2;
			//minion->init(enemyX, enemyY);

		break;
	}


	_vEnemy.push_back(minion);

}

void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

//======================================================================================== 에너미 셋팅 end