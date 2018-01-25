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
	//화면밖으로 사라지면 제거
	for (int i = 0; i < _vBeeto.size(); i++)
	{
		if (_vBeeto[i]->getRect().right < 200)
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
	for (int i = 0; i < 5; ++i)
	{
		minion1* minion;
		minion = new minion1;

		minion->init(500 + (i * 50), 350 - (i * 50));

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