#include "stdafx.h"
#include "frontObjectManager.h"
#include "playerManager.h"
#include "stageManager.h"


frontObjectManager::frontObjectManager()
{
}


frontObjectManager::~frontObjectManager()
{

}

HRESULT frontObjectManager::init()
{
	IMAGEMANAGER->addImage("grassLarge", ".\\image\\object\\grassLarge.bmp", 32, 16, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addImage("grassSmall", ".\\image\\object\\grassSmall.bmp", 16, 16, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("dirtBlockLarge", ".\\image\\object\\dirtBlockLarge.bmp", 320, 64, 5, 1, true, RGB(255, 0, 255), false);
	IMAGEMANAGER->addFrameImage("dirtPile", ".\\image\\object\\dirtPile.bmp", 165, 90, 5, 6, true, RGB(255, 0, 255), false);
	loadData();
	return S_OK;
}

void frontObjectManager::release()
{

}

void frontObjectManager::update() 
{
	objectInteraction();
}

void frontObjectManager::render() 
{
	if (_mapNum > 1)
	{
		for (int i = 0; i < _vObj[_mapNum - 2].size(); ++i)
		{
			if (_vObj[_mapNum - 2][i].isPresent == true)
			{
				if (_vObj[_mapNum - 2][i].type == 2) CAMERAMANAGER->frameRenderObject(getMemDC(), _vObj[_mapNum - 2][i].img, _vObj[_mapNum - 2][i].x, _vObj[_mapNum - 2][i].y, _vObj[_mapNum - 2][i].frameX, 0);
				else if (_vObj[_mapNum - 2][i].type == 7) CAMERAMANAGER->frameRenderObject(getMemDC(), _vObj[_mapNum - 2][i].img, _vObj[_mapNum - 2][i].x, _vObj[_mapNum - 2][i].y + 1, _vObj[_mapNum - 2][i].frameX, _vObj[_mapNum - 2][i].durability);
				else
				{
					CAMERAMANAGER->renderObject(getMemDC(), _vObj[_mapNum - 2][i].img, _vObj[_mapNum - 2][i].x, _vObj[_mapNum - 2][i].y);
				}
			}
		}
	}
}

void frontObjectManager::loadData()
{
	TCHAR key[255];
	for (int i = 0; i < 2; ++i)
	{
		char fileName[128];
		wsprintf(fileName, "object00%d", i + 2);
		char iniDir[128];
		wsprintf(iniDir, ".\\object00%d.ini", i + 2);
		int maxObject = INIDATA->loadDataInterger(fileName, "objectTotal", "maxNum");
		for (int j = 0; j < maxObject; ++j)
		{
			char dataName[128];
			wsprintf(dataName, "object%d", j + 1);
			GetPrivateProfileString(_T(dataName), _T("key"), NULL, key, 255, _T(iniDir));
			tagOBJECT tempObject;
			tempObject.img = IMAGEMANAGER->findImage(key);
			tempObject.type = INIDATA->loadDataInterger(fileName, dataName, "type");
			tempObject.x = INIDATA->loadDataInterger(fileName, dataName, "destX");
			tempObject.y = INIDATA->loadDataInterger(fileName, dataName, "destY");
			if (tempObject.type == 2)
			{
				tempObject.rc = RectMake(tempObject.x + 16, tempObject.y + 16, 32, 32);
				tempObject.frameX = 0;
				tempObject.count = 0;
				tempObject.isDestroyed = false;
			}
			if (tempObject.type == 7)
			{
				tempObject.rc = RectMake(tempObject.x, tempObject.y, 32, 16);
				tempObject.frameX = 0;
				tempObject.count = 0;
				tempObject.durability = 0;
				tempObject.isDestroyed = false;
			}
			tempObject.isPresent = true;
			_vObj[i].push_back(tempObject);
		}
	}
}

void frontObjectManager::mapColoring()
{
	if (_mapNum > 1)
	{
		for (int i = 0; i < _vObj[_mapNum - 2].size(); ++i)
		{
			if (_vObj[_mapNum - 2][i].type == 2 && _vObj[_mapNum - 2][i].isPresent == true)
			{
				HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), newPen);
				HBRUSH newBrush = CreateSolidBrush(RGB(0, 255, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), newBrush);

				Rectangle(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _vObj[_mapNum - 2][i].rc.left, _vObj[_mapNum - 2][i].rc.top, _vObj[_mapNum - 2][i].rc.right, _vObj[_mapNum - 2][i].rc.bottom);

				SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), oldBrush);
				DeleteObject(newBrush);
				DeleteObject(oldBrush);
				SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), oldPen);
				DeleteObject(newPen);
				DeleteObject(oldPen);
			}
		}
	}
}

void frontObjectManager::objectInteraction()
{
	if (_mapNum > 1)
	{
		for (int i = 0; i < _vObj[_mapNum - 2].size(); ++i)
		{
			if (_vObj[_mapNum - 2][i].isPresent == true)
			{

				if (_vObj[_mapNum - 2][i].type == 2)
				{
					if (_vObj[_mapNum - 2][i].isDestroyed == false)
					{
						RECT temp;
						if (IntersectRect(&temp, &_PM->getAttackRC(), &_vObj[_mapNum - 2][i].rc))
						{
							_PM->setPlayerReaction();
							HPEN newPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), newPen);
							HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 255));
							HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), newBrush);

							Rectangle(IMAGEMANAGER->findImage("bgMap")->getMemDC(), _vObj[_mapNum - 2][i].rc.left, _vObj[_mapNum - 2][i].rc.top, _vObj[_mapNum - 2][i].rc.right, _vObj[_mapNum - 2][i].rc.bottom);

							SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), oldBrush);
							DeleteObject(newBrush);
							DeleteObject(oldBrush);
							SelectObject(IMAGEMANAGER->findImage("bgMap")->getMemDC(), oldPen);
							DeleteObject(newPen);
							DeleteObject(oldPen);
							_vObj[_mapNum - 2][i].isDestroyed = true;
						}
					}
					if (_vObj[_mapNum - 2][i].isDestroyed == true)
					{
						_vObj[_mapNum - 2][i].count++;
						if (_vObj[_mapNum - 2][i].count > 10)
						{
							_vObj[_mapNum - 2][i].frameX++;
							if (_vObj[_mapNum - 2][i].frameX > 3)
							{
								_vObj[_mapNum - 2][i].isPresent = false;
							}
							_vObj[_mapNum - 2][i].count = 0;
						}
					}
				}
				if (_vObj[_mapNum - 2][i].type == 7)
				{
					if (_vObj[_mapNum - 2][i].isDestroyed == false)
					{
						RECT temp;
						if (IntersectRect(&temp, &_PM->getAttackRC(), &_vObj[_mapNum - 2][i].rc))
						{
							_vObj[_mapNum - 2][i].isDestroyed = true;
						}
					}
					if (_vObj[_mapNum - 2][i].isDestroyed == true)
					{
						_vObj[_mapNum - 2][i].count++;
						if (_vObj[_mapNum - 2][i].count > 4)
						{
							_vObj[_mapNum - 2][i].frameX++;
							if (_vObj[_mapNum - 2][i].frameX > 4)
							{
								_vObj[_mapNum - 2][i].frameX = 0;
								_vObj[_mapNum - 2][i].durability++;
								_vObj[_mapNum - 2][i].isDestroyed = false;
							}
							_vObj[_mapNum - 2][i].count = 0;
						}
					}
					if (_vObj[_mapNum - 2][i].durability >= 5)
					{
						_vObj[_mapNum - 2][i].isPresent = false;
					}
				}
			}
		}
	}
}
