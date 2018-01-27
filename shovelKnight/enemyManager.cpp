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
	setMinionBeeto();
	setMinionBlorb();
	setMinionDrake();


	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	//============================================================================ 적 move start
	//-------------------------------------------------------------- 미니언 beeto
	for (_viBeeto = _vBeeto.begin(); _viBeeto != _vBeeto.end(); ++_viBeeto)
	{

		(*_viBeeto)->update();
	
	}
	//데드 TEST
	for (int i = 0; i < _vBeeto.size(); i++)
	{
		if (_vBeeto[i]->getRect().right < 200)
		{
			if (_vBeeto[i]->getStatus() == ENEMY_LEFT_MOVE)
			{
				_vBeeto[i]->setStatus(ENEMY_LEFT_DEAD);
			}
			else if (_vBeeto[i]->getStatus() == ENEMY_RIGHT_MOVE)
			{
				_vBeeto[i]->setStatus(ENEMY_RIGHT_DEAD);
			}
		}
		//죽었으면 벡터에서 지우기
		if (_vBeeto[i]->getIsDeadVanish() == true)
		{
			removeMinionBeeto(i);
		}
	}
	//화면밖으로 사라지면 제거
	for (int i = 0; i < _vBeeto.size(); i++)
	{
		if (_vBeeto[i]->getRect().right < 0)
			removeMinionBeeto(i);
	}
	//-------------------------------------------------------------- 

	//-------------------------------------------------------------- 미니언 blorb
	for (_viBlorb = _vBlorb.begin(); _viBlorb != _vBlorb.end(); ++_viBlorb)
	{

		(*_viBlorb)->update();

	}
	//데드 TEST
	for (int i = 0; i < _vBlorb.size(); i++)
	{
		if (_vBlorb[i]->getRect().right < 200)
		{
			if (_vBlorb[i]->getStatus() == ENEMY_LEFT_MOVE)
			{
				_vBlorb[i]->setStatus(ENEMY_LEFT_DEAD);
			}
			else if (_vBlorb[i]->getStatus() == ENEMY_RIGHT_MOVE)
			{
				_vBlorb[i]->setStatus(ENEMY_RIGHT_DEAD);
			}
		}
		//죽었으면 벡터에서 지우기
		if (_vBlorb[i]->getIsDeadVanish() == true)
		{
			removeMinionBlorb(i);
		}
	}
	//화면밖으로 사라지면 제거
	for (int i = 0; i < _vBlorb.size(); i++)
	{
		if (_vBlorb[i]->getRect().right < 0)
			removeMinionBlorb(i);
	}
	//-------------------------------------------------------------- 

	//-------------------------------------------------------------- 미니언 drake
	for (_viDrake = _vDrake.begin(); _viDrake != _vDrake.end(); ++_viDrake)
	{

		(*_viDrake)->update();

	}
	//데드 TEST
	for (int i = 0; i < _vDrake.size(); i++)
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (_vDrake[i]->getStatus() == ENEMY_LEFT_MOVE)
			{
				_vDrake[i]->setStatus(ENEMY_LEFT_DEAD);
			}
			else if (_vDrake[i]->getStatus() == ENEMY_RIGHT_MOVE)
			{
				_vDrake[i]->setStatus(ENEMY_RIGHT_DEAD);
			}
		}
		//죽었으면 벡터에서 지우기
		if (_vDrake[i]->getIsDeadVanish() == true)
		{
			removeMinionBlorb(i);
		}
	}
	//화면밖으로 사라지면 제거
	for (int i = 0; i < _vDrake.size(); i++)
	{
		if (_vDrake[i]->getRect().right < 0)
			removeMinionBlorb(i);
	}
	//-------------------------------------------------------------- 
	//============================================================================ 적 move end
}

void enemyManager::render()
{
	//============================================================================ 적 render start
	//-------------------------------------------------------------- 미니언 beeto
	for (_viBeeto = _vBeeto.begin(); _viBeeto != _vBeeto.end(); ++_viBeeto)
	{

		(*_viBeeto)->render();

	}
	//--------------------------------------------------------------

	//-------------------------------------------------------------- 미니언 blorb
	for (_viBlorb = _vBlorb.begin(); _viBlorb != _vBlorb.end(); ++_viBlorb)
	{

		(*_viBlorb)->render();

	}
	//--------------------------------------------------------------

	//-------------------------------------------------------------- 미니언 drake
	for (_viDrake = _vDrake.begin(); _viDrake != _vDrake.end(); ++_viDrake)
	{

		(*_viDrake)->render();

	}
	//--------------------------------------------------------------
	//============================================================================ 적 render end
}



//================================================================== 미니언 셋팅 start
//-------------------------------------------------------------- beeto
void enemyManager::setMinionBeeto(void)
{
	for (int i = 0; i < 2; ++i)
	{
		minion1* minion;
		minion = new minion1;

		minion->init(900 + i * 200, 200 - 13);

		_vBeeto.push_back(minion);
	}
}

void enemyManager::removeMinionBeeto(int arrNum)
{
	SAFE_DELETE(_vBeeto[arrNum]);
	_vBeeto.erase(_vBeeto.begin() + arrNum);
}
//--------------------------------------------------------------

//-------------------------------------------------------------- blorb
void enemyManager::setMinionBlorb(void)
{
	for (int i = 0; i < 2; ++i)
	{
		minion2* minion;
		minion = new minion2;

		minion->init(800 + i * 200, 180);

		_vBlorb.push_back(minion);
	}
}

void enemyManager::removeMinionBlorb(int arrNum)
{
	SAFE_DELETE(_vBlorb[arrNum]);
	_vBlorb.erase(_vBlorb.begin() + arrNum);
}
//--------------------------------------------------------------

//-------------------------------------------------------------- drake
void enemyManager::setMinionDrake(void)
{
	for (int i = 0; i < 1; ++i)
	{
		minion3* minion;
		minion = new minion3;

		minion->init(1470, 130);

		_vDrake.push_back(minion);
	}
}

void enemyManager::removeMinionDrake(int arrNum)
{
	SAFE_DELETE(_vDrake[arrNum]);
	_vDrake.erase(_vDrake.begin() + arrNum);
}
//--------------------------------------------------------------
//================================================================== 미니언 셋팅 end