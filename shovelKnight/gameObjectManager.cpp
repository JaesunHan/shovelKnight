#include "stdafx.h"
#include "gameObjectManager.h"


gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}

virtual HRESULT init();
virtual void release();
virtual void update();
virtual void render();