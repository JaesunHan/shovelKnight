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
	//============================================================================ 적 render end
}



//================================================================== 미니언 셋팅 start
//-------------------------------------------------------------- beeto
void enemyManager::setMinionBeeto(void)
{
	for (int i = 0; i < 1; ++i)
	{
		minion1* minion;
		minion = new minion1;

		minion->init(500 + (i * 50), 100 - (i * 20));

		_vBeeto.push_back(minion);
	}
}

void enemyManager::removeMinionBeeto(int arrNum)
{
	SAFE_DELETE(_vBeeto[arrNum]);
	_vBeeto.erase(_vBeeto.begin() + arrNum);
}
//--------------------------------------------------------------
//================================================================== 미니언 셋팅 end