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

	_p1->getX();
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