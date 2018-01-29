#include "stdafx.h"
#include "playerManager.h"
#include "stageManager.h"
#include "gameCollision.h"
#include "skillManager.h"

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	_p1 = new player1;
	_p1->init();
	_p1->setSMMemoryAddressLink(_SM);
	_p1->setGameCollisinMemoryAddressLink(_GC);
	_p1->setSkillManagerMemoryAddressLink(_skillM);

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	_p1->update();
}

void playerManager::render()
{
	_p1->render();
}
