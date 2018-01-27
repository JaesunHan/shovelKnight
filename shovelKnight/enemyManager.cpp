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
	_enemyIsOn = true;

	//적 생성
	if (_enemyIsOn)
	{
		setEnemy(ENEMY_BEETO, 200, 200);
		setEnemy(ENEMY_BLORB, 300, 200);
		setEnemy(ELEMY_DRAKE, 400, 150);
		setEnemy(ENEMY_DRAGON, 500, 200);
	}


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
	//for (int i = 0; i < _vDragon.size(); i++)
	//{
	//	if (KEYMANAGER->isOnceKeyDown('K'))
	//	{
	//		if (_vDragon[i]->getStatus() == ENEMY_LEFT_MOVE)
	//		{
	//			_vDragon[i]->setStatus(ENEMY_LEFT_DEAD);
	//		}
	//		else if (_vDragon[i]->getStatus() == ENEMY_RIGHT_MOVE)
	//		{
	//			_vDragon[i]->setStatus(ENEMY_RIGHT_DEAD);
	//		}
	//	}
	//	//죽었으면 벡터에서 지우기
	//	if (_vDragon[i]->getIsDeadVanish() == true)
	//	{
	//		removeBossDragon(i);
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
	for (int i = 0; i < 2; ++i)
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
	
				//minion = new minion4;
				//minion->init(enemyX, enemyY);

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
}

void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

//======================================================================================== 에너미 셋팅 end