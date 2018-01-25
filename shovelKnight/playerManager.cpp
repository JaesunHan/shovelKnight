#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	_p1 = new player1;
	_p1->init(200 , 150);

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
