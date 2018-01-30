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

	//============================================================================ 적 카메라 아웃 소멸
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->getRect().right < 0)
			removeEnemy(i);
	}



	//============================================================================ 적 move start
	//-------------------------------------------------------------- 에너미 사망시 삭제
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		//죽었으면 벡터에서 지우기
		if (_vEnemy[i]->getIsDeadVanish() == true)
		{
			removeEnemy(i);
		}
	}

	//-------------------------------------------------------------- 에너미 update
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{

		(*_viEnemy)->update();
	
	}
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
void enemyManager::setEnemy(int enemyType, float enemyX, float enemyY)
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

			minion = new bossBlackKnight;
			minion->init(enemyX, enemyY);

		break;
	}


	_vEnemy.push_back(minion);

}

//                          에네미 종류          X좌표         Y좌표         움직임 패턴   
void enemyManager::setEnemy(int enemyType, float enemyX, float enemyY, int patternType)
{
	enemyBase* minion;

	switch (enemyType)
	{
	case ENEMY_BEETO:

		minion = new minion1;
		minion->init(enemyX, enemyY, patternType);

		break;
	case ENEMY_BLORB:

		minion = new minion2;
		minion->init(enemyX, enemyY, patternType);

		break;
	case ELEMY_DRAKE:

		minion = new minion3;
		minion->init(enemyX, enemyY, patternType);

		break;
	case ENEMY_SKELETON:

		minion = new skeleton;
		minion->init(enemyX, enemyY, patternType);

		break;
	case ENEMY_DRAGON:

		minion = new boss1;
		minion->init(enemyX, enemyY, patternType);

		break;
	case ENEMY_BLACKKNIGHT:

		minion = new bossBlackKnight;
		minion->init(enemyX, enemyY, patternType);

		break;
	}


	_vEnemy.push_back(minion);

}

void enemyManager::removeEnemy(int arrNum)
{
	SAFE_DELETE(_vEnemy[arrNum]);
	_vEnemy.erase(_vEnemy.begin() + arrNum);
}

void enemyManager::removeAllEnemy()
{
	for (int i= 0; i < _vEnemy.size(); ++i)
	{
		SAFE_DELETE(_vEnemy[i]);
		_vEnemy.erase(_vEnemy.begin() + i);
	}
}

void enemyManager::stageEnemySet(int stageNum)
{ 
	//예외처리
	if (stageNum >= 10) return;

	//현재 스테이지 에너미 셋 on
	_enemyIsOn[stageNum - 2] = true;

	if (_enemyIsOn[0]) 		//stage1
	{
		//setEnemy(ENEMY_BEETO, 300, 200);
		//setEnemy(ENEMY_BLORB, 350, 200);
		setEnemy(ELEMY_DRAKE, 300, 150, ENEMY_LEFT_FOWARD);
		setEnemy(ELEMY_DRAKE, 200, 200, ENEMY_PATROL);
		setEnemy(ENEMY_SKELETON, 350, 120);
		//setEnemy(ENEMY_DRAGON, 400, 179.5);
		setEnemy(ENEMY_BLACKKNIGHT, 350, 120);
	}
	if (_enemyIsOn[1])  //stage2
	{
		setEnemy(ELEMY_DRAKE, 400, 150);
		setEnemy(ENEMY_SKELETON, 350, 120);
	}
	if (_enemyIsOn[2])  //stage3
	{
		setEnemy(ENEMY_DRAGON, 400, 179.5);
	}
	if (_enemyIsOn[3])  //stage3
	{
		setEnemy(ENEMY_DRAGON, 400, 179.5);
	}
}

//======================================================================================== 에너미 셋팅 end