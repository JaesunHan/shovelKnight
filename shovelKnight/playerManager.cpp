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

	_p1->init(WINSIZEX / 2, WINSIZEY / 2, "¤¤¤¤");

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
}

void playerManager::render()
{
}
