#include "stdafx.h"
#include "gameObjectManager.h"


gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}


HRESULT gameObjectManager::init()
{
	IMAGEMANAGER->addFrameImage("dirtPile", ".//image//object//dirtPile.bmp", 165, 75, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("checkPoint", ".//image//object//checkPoint.bmp", 245, 53, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skeletonHead", ".//image//object//skeletonHead.bmp", 24, 11, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tresureBox", ".//image//object//tresureBox.bmp", 90, 23, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dirtBlock", ".//image//object//dirtBlock.bmp", 32, 32, true, RGB(255, 0, 255));






	return S_OK;
}

void gameObjectManager::release()
{
	
}

void gameObjectManager::update()
{


	for (int i = 0; i < _vObj.size(); ++i)
	{
		if (_vObj[i]->getDur() == 0 && _vObj[i]->getDelete())
		{
			SAFE_DELETE(_vObj[i]);
			_vObj.erase(_vObj.begin() + i);
		}
		_vObj[i]->update();
	}
}

void gameObjectManager::render()
{
	for (int i = 0; i < _vObj.size(); ++i)
	{
		_vObj[i]->render();
	}
}

void gameObjectManager::settingObject(float x, float y, OBJECTNUM obj)
{
	gameObjectBase* object;
	switch (obj)
	{
	case OBJ_DIRTBLOCK:	
		object =  new dirtBlock;
		break;
	case OBJ_DIRTPILE:
		object = new dirtPile;
		break;
	case OBJ_CHECKPOINT:
		object = new checkPoint;
		break;
	case OBJ_TRESUREBOX:
		object = new tresureBox;

		break;
	}
	object->init(x, y);
	_vObj.push_back(object);
}