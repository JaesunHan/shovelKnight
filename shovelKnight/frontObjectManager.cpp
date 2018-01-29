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
	loadData();
	return S_OK;
}

void frontObjectManager::release()
{

}

void frontObjectManager::update() 
{

}

void frontObjectManager::render() 
{
	//if (_mapNum > 1)
	//{
	//	for (_viObj = _vObj[_mapNum].begin(); _viObj != _vObj[_mapNum - 2].end(); ++_viObj)
	//	{
	//		if (_viObj->isPresent == true)
	//		{
	//			CAMERAMANAGER->renderObject(getMemDC(), IMAGEMANAGER->findImage("grassLarge"), _viObj->x, _viObj->y);
	//		}
	//	}
	//}
	//CAMERAMANAGER->renderObject(getMemDC(), IMAGEMANAGER->findImage("grassLarge"), _vObj[0][0].x, _vObj[0][0].y);
	CAMERAMANAGER->renderObject(getMemDC(), _vObj[0][0].img, _vObj[0][0].x, _vObj[0][0].y);
}

void frontObjectManager::loadData()
{
	TCHAR key[255];
	for (int i = 0; i < 1; ++i)
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
			tempObject.isPresent = true;
			_vObj[i].push_back(tempObject);
		}
	}
	/*
	char dataName[128];
	wsprintf(dataName, "map00%d", );
	char iniDir[128];
	wsprintf(iniDir, ".\\map00%d.ini", _mapNum);
	char txtDir[128];
	wsprintf(txtDir, "map00%d.txt", _mapNum);
	_maxLayer = INIDATA->loadDataInterger(mapName, "imageTotal", "maxNum");
	int maxTile = INIDATA->loadDataInterger(mapName, "tileTotal", "maxNum");
	int maxTransition = INIDATA->loadDataInterger(mapName, "transitionTotal", "maxNum");
	_maxFrameImage = INIDATA->loadDataInterger(mapName, "frameIamgeTotal", "maxNum");

	if (_maxLayer > 0)
	{
		for (int i = 0; i < _maxLayer; ++i)
		{
			char bgImage[128];
			wsprintf(bgImage, "bgImage%d", i + 1);
			GetPrivateProfileString(_T(bgImage), _T("key"), NULL, key, 255, _T(iniDir));
			GetPrivateProfileString(_T(bgImage), _T("directory"), NULL, directory, 255, _T(iniDir));
			if (IMAGEMANAGER->findImage(key)) IMAGEMANAGER->deleteImage(key);
			IMAGEMANAGER->addImage(key, directory,
				INIDATA->loadDataInterger(mapName, bgImage, "width"),
				INIDATA->loadDataInterger(mapName, bgImage, "height"),
				true, RGB(255, 0, 255), false);
		}
	}
	*/
}